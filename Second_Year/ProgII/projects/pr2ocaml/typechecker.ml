open Interpreter

(** Exceptions **)
exception StaticTypeErr of string
exception UnboundVariable

(** Functions on the type environment **)

(* empty_tenv returns an empty environment *)
let empty_tenv : typ env = []
(* tbind adds a new binding to a pre-existing environment *)
let tbind (env : typ env) (x : ide) (v : typ) = (x, v)::env
(* lookup looks for the type of the variable identified by x in the environment *)
let rec tlookup (env : typ env) (x : ide) = 
  match env with
  | []                    -> raise UnboundVariable
  | (a, v)::_ when a = x  -> v
  | _::e                  -> tlookup e x

(* The static typechecker *)
let rec typeof (e : expr) (tenv : typ env) : typ = 
  match e with
  | LitInt _ -> IntTy
  | LitTrue -> BoolTy
  | LitFalse -> BoolTy
  | LitStr _ -> StrTy
  | Den var -> tlookup tenv var
  | Add (e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | IntTy, IntTy -> IntTy
    | _ -> raise (StaticTypeErr "Add must take two integer arguments") )
  | Sub (e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | IntTy, IntTy -> IntTy
    | _ -> raise (StaticTypeErr "Sub must take two integer arguments") )
  | Times (e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | IntTy, IntTy -> IntTy
    | _ -> raise (StaticTypeErr "Times must take two integer arguments") )
  | IsZero e -> 
    if typeof e tenv = IntTy 
      then BoolTy
      else raise (StaticTypeErr "IsZero must take an integer argument")
  | Equals (e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | IntTy, IntTy -> BoolTy
    | _ -> raise (StaticTypeErr "Equals must take two integer arguments") )
  | And (e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | BoolTy, BoolTy -> BoolTy
    | _ -> raise (StaticTypeErr "And must take two boolean arguments") )
  | Or (e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | BoolTy, BoolTy -> BoolTy
    | _ -> raise (StaticTypeErr "Or must take two boolean arguments") )
  | Not e -> 
    ( match typeof e tenv with
    | BoolTy -> BoolTy
    | _ -> raise (StaticTypeErr "Not must take a boolean argument") )
  | IfThenElse (cond, e1, e2) ->
    if typeof cond tenv = BoolTy
      then (
        let t1 = typeof e1 tenv in
        let t2 = typeof e2 tenv in
          if t1 = t2 then t1 else raise (StaticTypeErr "Then and Else branch must have the same type")
      ) 
      else raise (StaticTypeErr "IfThenElse's first argument must be a boolean")
  | Let (id, e1, e2) -> 
    let t1 = typeof e1 tenv in
      typeof e2 (tbind tenv id t1)
  | Fun (id, body, t1, t2) ->
    let boundEnv = tbind tenv id t1 in
    let t_res = typeof body boundEnv in
      if t_res = t2 then FunTy(t1, t_res)
      else raise (StaticTypeErr "Return type annotation is wrong")
  | LetRec (funId, param, t1, t2, funBody, letBody) ->
    let tenv' = tbind tenv param t1 in
    let boundEnv = tbind tenv' funId (FunTy(t1, t2)) in
      if typeof funBody boundEnv = t2
        then typeof letBody boundEnv
        else raise (StaticTypeErr "Return type annotation is wrong")
  | Apply (func, arg) ->
    ( match typeof func tenv with
    | FunTy(t1, t2) -> 
      if typeof arg tenv = t1 then t2
      else raise (StaticTypeErr "Function argument has the wrong type")
    | _ -> raise (StaticTypeErr "Apply's first argument must be a function") )
  (* set constructors *)
  | EmptySet(ty) -> SetTy(ty)
  | Singleton(ty, e1) -> 
    if typeof e1 tenv = ty then SetTy(ty)
    else raise (StaticTypeErr "Values in a set must all have the given type")
  | Of(ty, set_e) ->
    let rec check_all_set (ty : typ) (set_e : set_expr) : bool =
      match set_e with
      | Empty -> true
      | Cons(e, es) -> (typeof e tenv = ty) && check_all_set ty es
    in 
    if check_all_set ty set_e then SetTy(ty)
    else raise (StaticTypeErr "Values in a set must all have the given type")
  (* base operations *)
  | Union(e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | SetTy(t1), SetTy(t2) -> 
      if t1 = t2 then SetTy(t1)
      else raise (StaticTypeErr "Union type error: the two sets have different types")
    | _ -> raise (StaticTypeErr "Union must take two sets with the same element type") )
  | Inters(e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | SetTy(t1), SetTy(t2) -> 
      if t1 = t2 then SetTy(t1)
      else raise (StaticTypeErr "Inters type error: the two sets have different types")
    | _ -> raise (StaticTypeErr "Inters must take two sets with the same element type") )
  | SetDiff(e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | SetTy(t1), SetTy(t2) -> 
      if t1 = t2 then SetTy(t1)
      else raise (StaticTypeErr "SetDiff type error: the two sets have different types")
    | _ -> raise (StaticTypeErr "SetDiff must take two sets with the same element type") )
  | Insert(e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | t1, SetTy(t2) -> 
      if t1 = t2 then SetTy(t1)
      else raise (StaticTypeErr "Insert type error: the element and the set have different types")
    | _ -> raise (StaticTypeErr "Insert must take a value and a set with the same type") )
  | Remove(e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | t1, SetTy(t2) -> 
      if t1 = t2 then SetTy(t1)
      else raise (StaticTypeErr "Remove type error: the element and the set have different types")
    | _ -> raise (StaticTypeErr "Remove must take a value and a set with the same type") )
  | Contains(e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | t1, SetTy(t2) -> 
      if t1 = t2 then BoolTy
      else raise (StaticTypeErr "Contains type error: the element and the set have different types")
    | _ -> raise (StaticTypeErr "Contains must take a value and a set with the same type") )
  | Subset(e1, e2) -> 
    ( match typeof e1 tenv, typeof e2 tenv with
    | SetTy(t1), SetTy(t2) -> 
      if t1 = t2 then BoolTy
      else raise (StaticTypeErr "Subset type error: the two sets have different types")
    | _ -> raise (StaticTypeErr "Subset must take two sets with the same element type") )
  | IsEmpty(e) ->
    ( match typeof e tenv with
    | SetTy(_) -> BoolTy
    | _ -> raise (StaticTypeErr "IsEmpty must take a set") )
  | MinOf(e) -> 
    ( match typeof e tenv with
    | SetTy(t) -> 
      if t = IntTy || t = StrTy || t = BoolTy then t
      else raise (StaticTypeErr "MinOf type error: the sets must be a set of integers, booleans or string")
    | _ -> raise (StaticTypeErr "MinOf must take a set") )
  | MaxOf(e) -> 
    ( match typeof e tenv with
    | SetTy(t) -> 
      if t = IntTy || t = StrTy || t = BoolTy then t
      else raise (StaticTypeErr "MaxOf type error: the sets must be a set of integers, booleans or string")
    | _ -> raise (StaticTypeErr "MaxOf must take a set") )
  (* functional operators *)
  | ForAll(p, e) ->
    ( match typeof p tenv, typeof e tenv with
    | FunTy(t1, BoolTy), SetTy(t2) ->
      if t1 = t2 then BoolTy
      else raise (StaticTypeErr "ForAll type error: type mismatch between predicate and set")
    | _ -> raise (StaticTypeErr "ForAll must take a predicate and a set") )
  | Exists(p, e) ->
    ( match typeof p tenv, typeof e tenv with
    | FunTy(t1, BoolTy), SetTy(t2) ->
      if t1 = t2 then BoolTy
      else raise (StaticTypeErr "Exists type error: type mismatch between predicate and set")
    | _ -> raise (StaticTypeErr "Exists must take a predicate and a set") )  
  | Filter(p, e) ->
    ( match typeof p tenv, typeof e tenv with
    | FunTy(t1, BoolTy), SetTy(t2) ->
      if t1 = t2 then SetTy(t1)
      else raise (StaticTypeErr "Filter type error: type mismatch between predicate and set")
    | _ -> raise (StaticTypeErr "Filter must take a predicate and a set") )
  | Map(f, e) ->
    ( match typeof f tenv, typeof e tenv with
    | FunTy(t1, t), SetTy(t2) ->
      if t1 = t2 then SetTy(t)
      else raise (StaticTypeErr "Map type error: type mismatch between function and set")
    | _ -> raise (StaticTypeErr "Map must take a function and a set") )

let typeof' t = typeof t empty_tenv

let check_eval e = let _ = typeof' e in (); eval' e