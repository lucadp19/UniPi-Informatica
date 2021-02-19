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
  | IsZero of expr * expr
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

(* Functions on the environment *)

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