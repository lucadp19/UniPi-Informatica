(* ide represents a variable identifier *)
type ide = string

(* expr is the Abstract Syntax Tree of the language*)
type expr = 
  | LitTrue
  | LitFalse
  | LitInt of int
  | Den of ide 
  | Add of expr * expr
  | Sub of expr * expr 
  | Times of expr * expr
  | IsZero of expr
  | Equals of expr * expr
  | IfThenElse of expr * expr * expr
  | Let of ide * expr * expr
  | Fun of ide * expr
  | LetRec of ide * ide * expr * expr
  | Apply of expr * expr

(* The polymorphic environment *)
type 'v env = (string * 'v) list

(* Runtime values *)
type evT =
  | Int of int
  | Bool of bool
  | Closure of ide * expr * evT env
  | RecClosure of ide * ide * expr * evT env
  | Unbound

(* Type-tags for convenience when typechecking expressions *)
type typeTag =
  | IntTag
  | BoolTag

(** Functions on the values environment **)

(* empty_env returns an empty environment *)
let empty_env : evT env = [("", Unbound)]
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
  | IntTag -> ( match v with
                | Int _ -> true
                | _     -> false)
  | BoolTag -> ( match v with
                | Bool _ -> true
                | _      -> false)

exception TypeError

(* Auxiliary evaluators *)
let int_add (n : evT) (m : evT) : evT =
  match typecheck IntTag n, typecheck IntTag m, n, m with
  | true, true, Int a, Int b -> Int (a + b)
  | _, _, _, _               -> raise TypeError

let int_sub (n : evT) (m : evT) : evT =
  match typecheck IntTag n, typecheck IntTag m, n, m with
  | true, true, Int a, Int b -> Int (a - b)
  | _, _, _, _               -> raise TypeError

let int_times (n : evT) (m : evT) : evT =
  match typecheck IntTag n, typecheck IntTag m, n, m with
  | true, true, Int a, Int b -> Int (a * b)
  | _, _, _, _               -> raise TypeError

let is_zero (n : evT) : evT =
  match typecheck IntTag n, n with
  | true, Int a -> Bool (a = 0)
  | _, _        -> raise TypeError

let int_equals (v1 : evT) (v2 : evT) : evT =
  match typecheck IntTag v1, typecheck IntTag v2, v1, v2 with
  | true, true, Int n, Int m -> Bool (n = m)
  | _, _, _, _               -> raise TypeError

(* Main evaluating function *)
let rec eval (e : expr) (env : evT env) : evT =
  match e with
  | LitInt n        -> Int n
  | LitTrue         -> Bool true
  | LitFalse        -> Bool false
  | Den id          -> lookup env id
  | Add (e1, e2)    -> int_add (eval e1 env) (eval e2 env)
  | Sub (e1, e2)    -> int_sub (eval e1 env) (eval e2 env)
  | Times (e1, e2)  -> int_times (eval e1 env) (eval e2 env)
  | IsZero e        -> is_zero (eval e env)
  | Equals (e1, e2) -> int_equals (eval e1 env) (eval e2 env)
  | IfThenElse (cond, e1, e2) -> 
    ( let evaledCond = eval cond env in
        match typecheck BoolTag evaledCond, evaledCond with 
        | true, Bool true   -> eval e1 env 
        | true, Bool false  -> eval e2 env 
        | _                 -> raise TypeError )
  | Let (id, e1, e2) -> eval e2 (bind env id (eval e1 env))
  | Fun (id, body) -> Closure (id, body, env)
  | LetRec (funId, param, funBody, letBody) ->
      let recClos = RecClosure (funId, param, funBody, env) in
      let bindEnv = bind env funId recClos in
        eval letBody bindEnv
  | Apply (Den funName, arg) ->
      (* Den f should be the name of a function in the environment *)
      let funClosure = lookup env funName in
        ( match funClosure with
            (* First case: f is evaluated to a closure *)
            | Closure (param, funBody, funDeclEnv) -> 
                let actualVal = eval arg env in
                let actualEnv = bind funDeclEnv param actualVal in
                  eval funBody actualEnv
            | RecClosure (funId, param, funBody, funDeclEnv) ->
                let actualVal = eval arg env in
                let recEnv = bind funDeclEnv funName funClosure in
                let actualEnv = bind recEnv param actualVal in
                  eval funBody actualEnv
            | _ -> raise TypeError )
  | Apply (_, _) -> raise TypeError
