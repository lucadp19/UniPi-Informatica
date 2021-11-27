(* ide represents a variable identifier *)
type ide = string

(* typ represents the allowed types in the language *)
type typ = 
  | IntTy
  | BoolTy
  | StrTy
  | FunTy of typ * typ
  | SetTy of typ

(* expr is the Abstract Syntax Tree of the language*)
type expr = 
  | LitTrue
  | LitFalse
  | LitInt of int
  | LitStr of string
  | Den of ide 
  | Add of expr * expr
  | Sub of expr * expr 
  | Times of expr * expr
  | IsZero of expr
  | Equals of expr * expr
  | And of expr * expr
  | Or of expr * expr
  | Not of expr
  | IfThenElse of expr * expr * expr
  | Let of ide * expr * expr
  | Fun of ide * expr * typ * typ
  | LetRec of ide * ide * typ * typ * expr * expr
  | Apply of expr * expr
  (* Set constructors *)
  | EmptySet of typ
  | Singleton of typ * expr
  | Of of typ * set_expr
  (* Basic operations *)
  | Union of expr * expr
  | Inters of expr * expr
  | SetDiff of expr * expr
  (* Additional operations *)
  | Insert of expr * expr
  | Remove of expr * expr
  | Contains of expr * expr
  | Subset of expr * expr
  | IsEmpty of expr
  | MinOf of expr
  | MaxOf of expr
  (* Functional operators *)
  | ForAll of expr * expr
  | Exists of expr * expr
  | Filter of expr * expr
  | Map of expr * expr
and set_expr =
  | Empty
  | Cons of expr * set_expr

(* The polymorphic environment *)
type 'v env = (string * 'v) list

(* Runtime values *)
type evT =
  | Int of int
  | Bool of bool
  | Str of string
  | Closure of ide * expr * evT env * typ * typ
  | RecClosure of ide * ide * expr * evT env * typ * typ
  | Set of typ * set_val
  | Unbound
and set_val =
  | EmptyV
  | ConsV of evT * set_val

(* Type-tags for convenience when typechecking expressions *)
type typeTag =
  | IntTag
  | BoolTag
  | StrTag
  | FunTag
  | SetTag

(** Functions on the values environment **)

(* empty_env returns an empty environment *)
let empty_env : evT env = []
(* bind adds a new binding to a pre-existing environment *)
let bind (env : evT env) (x : ide) (v : evT) = (x, v)::env
(* lookup looks for the value of the variable identified by x in the environment *)
let rec lookup (env : evT env) (x : ide) = 
  match env with
  | []                    -> Unbound
  | (a, v)::_ when a = x  -> v
  | _::e                  -> lookup e x


(* Dynamic typechecking function *)
let rec typecheck (tag : typeTag) (v : evT) = 
  match tag with 
  | IntTag -> 
    ( match v with
    | Int _ -> true
    | _     -> false )
  | BoolTag -> 
    ( match v with
    | Bool _ -> true
    | _      -> false )
  | StrTag -> 
    ( match v with
    | Str _ -> true
    | _     -> false )
  | FunTag -> 
    ( match v with
    | Closure _    -> true
    | RecClosure _ -> true
    | _            -> false )
  | SetTag -> 
    ( match v with
    | Set _ -> true
    | _     -> false )

let check_from_lang_ty (ty : typ) : evT -> bool =
  match ty with
  | IntTy -> typecheck IntTag
  | BoolTy -> typecheck BoolTag
  | StrTy -> typecheck StrTag
  | FunTy _ -> typecheck FunTag
  | SetTy _ -> typecheck SetTag

exception DynamicTypeErr of string
exception SetIsEmpty of string

(* Auxiliary evaluators *)
let int_add (n : evT) (m : evT) : evT =
  match typecheck IntTag n, typecheck IntTag m, n, m with
  | true, true, Int a, Int b -> Int (a + b)
  | _, _, _, _               -> raise (DynamicTypeErr "Add only accepts two integers")

let int_sub (n : evT) (m : evT) : evT =
  match typecheck IntTag n, typecheck IntTag m, n, m with
  | true, true, Int a, Int b -> Int (a - b)
  | _, _, _, _               -> raise (DynamicTypeErr "Sub only accepts two integers")

let int_times (n : evT) (m : evT) : evT =
  match typecheck IntTag n, typecheck IntTag m, n, m with
  | true, true, Int a, Int b -> Int (a * b)
  | _, _, _, _               -> raise (DynamicTypeErr "Times only accepts two integers")

let is_zero (n : evT) : evT =
  match typecheck IntTag n, n with
  | true, Int a -> Bool (a = 0)
  | _, _        -> raise (DynamicTypeErr "IsZero's parameter must be an integer")

let int_equals (v1 : evT) (v2 : evT) : evT =
  match typecheck IntTag v1, typecheck IntTag v2, v1, v2 with
  | true, true, Int n, Int m -> Bool (n = m)
  | _, _, _, _               -> raise (DynamicTypeErr "Equals only accepts two integers")

let bool_and (v1 : evT) (v2 : evT) : evT =
  match typecheck BoolTag v1, typecheck BoolTag v2, v1, v2 with
  | true, true, Bool b, Bool p -> Bool (b && p)
  | _, _, _, _                 -> raise (DynamicTypeErr "And only accepts two booleans")

let bool_or (v1 : evT) (v2 : evT) : evT =
  match typecheck BoolTag v1, typecheck BoolTag v2, v1, v2 with
  | true, true, Bool b, Bool p -> Bool (b || p)
  | _, _, _, _                 -> raise (DynamicTypeErr "Or only accepts two booleans")

let bool_not (v : evT) : evT =
  match typecheck BoolTag v, v with
  | true, Bool b -> Bool (not b)
  | _, _         -> raise (DynamicTypeErr "Not only accepts a boolean")

let rec set_contains (s : set_val) (v : evT) : bool =
  match s with
  | EmptyV -> false
  | ConsV (v', _) when v' = v -> true
  | ConsV (_, s') -> set_contains s' v

let rec set_union (s1 : set_val) (s2 : set_val) : set_val =
  match s1 with
  | EmptyV -> s2
  | ConsV (v1, s1') -> 
    if set_contains s2 v1 
      then set_union s1' s2
      else set_union s1' (ConsV(v1, s2))

let rec set_inters (s1 : set_val) (s2 : set_val) : set_val =
  match s1 with
  | EmptyV -> EmptyV
  | ConsV (v1, s1') -> 
    if set_contains s2 v1 
      then ConsV(v1, (set_inters s1' s2))
      else set_inters s1' s2

let rec set_diff (s1 : set_val) (s2 : set_val) : set_val =
  match s1 with
  | EmptyV -> EmptyV
  | ConsV (v1, s1') ->
    if set_contains s2 v1
      then set_diff s1' s2
      else ConsV(v1, (set_diff s1' s2))

let rec set_remove (s : set_val) (v : evT): set_val =
  match s with
  | EmptyV -> EmptyV
  | ConsV (v', s') when v' = v -> s'
  | ConsV (v', s') -> ConsV (v', set_remove s' v)

let rec set_subset (s1 : set_val) (s2 : set_val) : bool =
  match s1 with
  | EmptyV -> true
  | ConsV (v', s') -> 
    if set_contains s2 v' 
      then set_subset s' s2
      else false

let rec set_min (s : set_val) : evT =
  let min n m = if n < m then n else m in
    match s with
    | EmptyV -> raise (SetIsEmpty "Cannot compute the minimum of an empty set")
    | ConsV (v, EmptyV) -> v
    | ConsV (v, s') ->
      ( match set_min s', v with
        | Int m, Int n -> Int (min m n)
        | Str s, Str z -> Str (min s z)
        | Bool b, Bool p -> Bool (min b p)
        | a, b -> raise (DynamicTypeErr "min calculation failed") )

let rec set_max (s : set_val) : evT =
  let max n m = if n > m then n else m in
    match s with
    | EmptyV -> raise (SetIsEmpty "Cannot compute the maximum of an empty set")
    | ConsV (v, EmptyV) -> v
    | ConsV (v, s') ->
      ( match set_max s', v with
        | Int m, Int n -> Int (max m n)
        | Str s, Str z -> Str (max s z)
        | Bool b, Bool p -> Bool (max b p)
        | a, b -> raise (DynamicTypeErr "max calculation failed"))     

(* Main evaluating function *)
let rec eval (e : expr) (env : evT env) : evT =
  match e with
  | LitInt n        -> Int n
  | LitTrue         -> Bool true
  | LitFalse        -> Bool false
  | LitStr s        -> Str s
  | Den id          -> lookup env id
  | Add (e1, e2)    -> int_add (eval e1 env) (eval e2 env)
  | Sub (e1, e2)    -> int_sub (eval e1 env) (eval e2 env)
  | Times (e1, e2)  -> int_times (eval e1 env) (eval e2 env)
  | IsZero e        -> is_zero (eval e env)
  | Equals (e1, e2) -> int_equals (eval e1 env) (eval e2 env)
  | And (e1, e2)    -> bool_and (eval e1 env) (eval e2 env)
  | Or (e1, e2)     -> bool_or  (eval e1 env) (eval e2 env)
  | Not (e)         -> bool_not (eval e env)
  | IfThenElse (cond, e1, e2) -> 
    ( let evalCond = eval cond env in
        match typecheck BoolTag evalCond, evalCond with 
        | true, Bool true   -> eval e1 env 
        | true, Bool false  -> eval e2 env 
        | _                 -> raise (DynamicTypeErr "IfThenElse's first argument must be a boolean") )
  | Let (id, e1, e2) -> eval e2 (bind env id (eval e1 env))
  | Fun (id, body, t1, t2) -> Closure (id, body, env, t1, t2)
  | LetRec (funId, param, t1, t2, funBody, letBody) ->
      let recClos = RecClosure (funId, param, funBody, env, t1, t2) in
      let bindEnv = bind env funId recClos in
        eval letBody bindEnv
  | Apply (func, arg) ->
      (* func should be evaluated to a function, either named or anonymous *)
      let funClosure = eval func env in
        ( match funClosure with
          (* First case: f is evaluated to a closure *)
          | Closure (param, funBody, funDeclEnv, t1, _) -> 
              let actualVal = eval arg env in
              if check_from_lang_ty t1 actualVal = true 
                then 
                  ( let actualEnv = bind funDeclEnv param actualVal in
                    eval funBody actualEnv )
                else raise (DynamicTypeErr "Apply failed: actual argument has the wrong type")
          (* Second case: f is a recursive closure *)
          | RecClosure (funId, param, funBody, funDeclEnv, t1, _) ->
              let actualVal = eval arg env in
              if check_from_lang_ty t1 actualVal = true
                then 
                  ( let recEnv = bind funDeclEnv funId funClosure in
                    let actualEnv = bind recEnv param actualVal in
                      eval funBody actualEnv )
                else raise (DynamicTypeErr "Apply failed: actual argument has the wrong type")
          | _ -> raise (DynamicTypeErr "Apply failed: first argument is not a function") )
  (* Set constructors *)
  | EmptySet ty -> Set (ty, EmptyV)
  | Singleton (ty, exp) -> 
      let v = eval exp env in
        if check_from_lang_ty ty v 
          then Set (ty, ConsV (v, EmptyV))
          else raise (DynamicTypeErr "set value does not correspond to type")
  | Of (ty, set_e) -> 
      let rec check_whole_set (ty : typ) (set_v : set_val) : bool =
        ( match set_v with
          | EmptyV -> true
          | ConsV (v, set_v') ->
            ( if check_from_lang_ty ty v 
                then check_whole_set ty set_v'
                else false )) in
      let set_v = set_eval set_e env in
        if check_whole_set ty set_v
          then Set (ty, set_v)
          else raise (DynamicTypeErr "set values do not correspond to type")
  (* Base operations *)
  | Union (e1, e2) ->
    ( match eval e1 env, eval e2 env with
      | Set(t1, set_v1), Set(t2, set_v2) when t1 = t2 ->
        Set(t1, set_union set_v1 set_v2)
      | _, _ -> raise (DynamicTypeErr "Union failed: set types must be equal") )
  | Inters (e1, e2) ->
    ( match eval e1 env, eval e2 env with
      | Set(t1, set_v1), Set(t2, set_v2) when t1 = t2 ->
        Set(t1, set_inters set_v1 set_v2)
      | _, _ -> raise (DynamicTypeErr "Inters failed: set types must be equal") )
  | SetDiff (e1, e2) ->
    ( match eval e1 env, eval e2 env with
      | Set(t1, set_v1), Set(t2, set_v2) when t1 = t2 ->
        Set(t1, set_diff set_v1 set_v2)
      | _, _ -> raise (DynamicTypeErr "SetDiff failed: set types must be equal") )
  | Insert (e, set_e) ->
    ( match eval set_e env with
      | Set(ty, set_v) -> 
        let v = eval e env in
          if check_from_lang_ty ty v && not (set_contains set_v v)
            then Set(ty, ConsV(v, set_v))
            else Set(ty, set_v) 
      | _ -> raise (DynamicTypeErr "Insert failed: value does not correspond to set type") )
  | Remove (e, set_e) ->
    ( match eval set_e env with
      | Set(ty, set_v) -> Set(ty, set_remove set_v (eval e env))
      | _ -> raise (DynamicTypeErr "Remove failed: value does not correspond to set type") )
  | Contains (e, set_e) ->
    ( match eval set_e env with
      | Set(ty, set_v) -> Bool (set_contains set_v (eval e env))
      | _ -> raise (DynamicTypeErr "Contains failed: value does not correspond to set type") )
  | Subset (set_e1, set_e2) ->
    ( match eval set_e1 env, eval set_e2 env with
      | Set(t1, set_v1), Set(t2, set_v2) ->
        if t1 = t2 
          then Bool (set_subset set_v1 set_v2)
          else raise (DynamicTypeErr "Subset failed: set types must be equal")
      | _, _ -> raise (DynamicTypeErr "Subset only accepts two sets") )
  | IsEmpty (set_e) ->
    ( match eval set_e env with
      | Set(_, set_v) -> if set_v = EmptyV then Bool true else Bool false
      | _ -> raise (DynamicTypeErr "IsEmpty's argument must be a set") )
  | MinOf set_e ->
    ( match eval set_e env with
      | Set(ty, set_v) ->
        if ty = IntTy || ty = StrTy || ty = BoolTy
          then set_min set_v
          else raise (DynamicTypeErr "MinOf failed: set must be of type Int, Bool or String")
      | _ -> raise (DynamicTypeErr "MinOf only accepts a set as argument") )
  | MaxOf set_e ->
    ( match eval set_e env with
      | Set(ty, set_v) ->
        if ty = IntTy || ty = StrTy || ty = BoolTy
          then set_max set_v
          else raise (DynamicTypeErr "MaxOf failed: set must be of type Int, Bool or String")
      | _ -> raise (DynamicTypeErr "MaxOf only accepts a set as argument") )
  | ForAll (pred, set_e) ->
    ( match eval pred env, eval set_e env with
      | Closure(param, funBody, funDeclEnv, t1, t2) as funClosure, Set(ty, set_v) ->
        if t1 = ty && t2 = BoolTy
          then set_forall funClosure set_v 
          else raise (DynamicTypeErr "ForAll failed: first argument must be a non-recursive function with the same input type as the set, and the result type must be Bool")
      | _ -> raise (DynamicTypeErr "ForAll only accepts a predicate and a set") )
  | Exists (pred, set_e) ->
    ( match eval pred env, eval set_e env with
      | Closure(param, funBody, funDeclEnv, t1, t2) as funClosure, Set(ty, set_v) ->
        if t1 = ty && t2 = BoolTy
          then set_exists funClosure set_v 
          else raise (DynamicTypeErr "Exists failed: first argument must be a non-recursive function with the same input type as the set, and the result type must be Bool")
      | _ -> raise (DynamicTypeErr "Exists only accepts a predicate and a set") )
  | Filter (pred, set_e) ->
    ( match eval pred env, eval set_e env with
      | Closure(param, funBody, funDeclEnv, t1, t2) as funClosure, Set(ty, set_v) ->
        if t1 = ty && t2 = BoolTy
          then Set(ty, set_filter funClosure set_v) 
          else raise (DynamicTypeErr "Filter failed: first argument must be a non-recursive function with the same input type as the set, and the result type must be Bool")
      | _ -> raise (DynamicTypeErr "Filter only accepts a predicate and a set") )
  | Map (func, set_e) ->
    ( match eval func env, eval set_e env with
      | Closure(param, funBody, funDeclEnv, t1, t2) as funClosure, Set(ty, set_v) ->
        if t1 = ty
          then Set(t2, set_map funClosure set_v)
          else raise (DynamicTypeErr "Map failed: first argument must be a non-recursive function with the same input type as the set")
      | _ -> raise (DynamicTypeErr "Map only accepts a predicate and a set") )

and set_eval (set_e : set_expr) (env : evT env) : set_val = 
  match set_e with
  | Empty -> EmptyV
  | Cons (e, set_e') -> 
    let set_v' = set_eval set_e' env in
    let v = eval e env in
      if set_contains set_v' v
        then set_v'
        else ConsV (v, set_v')

and set_forall (closure : evT) (set_v : set_val) : evT =
  match set_v with
  | EmptyV -> Bool true
  | ConsV (v', s') ->
    ( match closure with
    | Closure(param, funBody, funDeclEnv, _, _) ->
      let actualEnv = bind funDeclEnv param v' in
        ( match eval funBody actualEnv with
        | Bool value -> 
          if (not value) 
            then Bool false
            else set_forall closure s' 
        | _ -> raise (DynamicTypeErr "set_forall failed: predicate must return a boolean"))
    | _ -> raise (DynamicTypeErr "set_forall failed: first argument must be a closure"))
  
and set_exists (closure : evT) (set_v : set_val) : evT =
  match set_v with
  | EmptyV -> Bool false
  | ConsV (v', s') ->
    ( match closure with
    | Closure(param, funBody, funDeclEnv, _, _) ->
      let actualEnv = bind funDeclEnv param v' in
        ( match eval funBody actualEnv with
        | Bool value -> 
          if value 
            then Bool true
            else set_exists closure s'
        | _ -> raise (DynamicTypeErr "set_exists failed: predicate must return a boolean"))
    | _ -> raise (DynamicTypeErr "set_exists failed: first argument must be a closure"))

and set_filter (closure : evT) (set_v : set_val) : set_val =
  match set_v with
  | EmptyV -> EmptyV
  | ConsV (v', s') ->
    ( match closure with
    | Closure(param, funBody, funDeclEnv, _, _) ->
      let actualEnv = bind funDeclEnv param v' in
        ( match eval funBody actualEnv with
        | Bool ok -> 
            let rest = set_filter closure s' in
              if ok then ConsV(v', rest) else rest
        | _ -> raise (DynamicTypeErr "set_filter failed: predicate must return a boolean"))
    | _ -> raise (DynamicTypeErr "set_filter failed: first argument must be a closure"))
    
and set_map (closure : evT) (set_v : set_val) : set_val =
  match set_v with
  | EmptyV -> EmptyV
  | ConsV (v', s') ->
    ( match closure with
    | Closure(param, funBody, funDeclEnv, _, t2) ->
      let actualEnv = bind funDeclEnv param v' in
      let result = eval funBody actualEnv in
      let rest = set_map closure s' in
        if check_from_lang_ty t2 result = true
          then (if not (set_contains rest result) then ConsV(result, rest) else rest)
          else raise (DynamicTypeErr "set_map failed: function application returned a value with the wrong type")
    | _ -> raise (DynamicTypeErr "set_map failed: first argument must be a closure") ) 

let ( @: ) (e : expr) (set_e : set_expr) : set_expr =
  Cons (e, set_e)

let eval' t = eval t empty_env