type label = Lab of string
type expr = 
  | LitInt of int
  | LitFalse
  | LitTrue
  | Add of expr * expr
  | Record of (label * expr) list
  | Select of (expr * label)

exception TypeMismatch
exception FieldNotFound

type evT = 
  | Int of int
  | Bool of bool
  | RecordEv of (label * evT) list

let rec lookupRecord (body : (label * evT) list) (lab : label) :evT =
  match body with
  | [] -> raise FieldNotFound
  | (lab', value)::rs -> if lab' = lab then value
                          else lookupRecord rs lab 

let rec evalRecord (body : (label * expr) list) =
  match body with
  | [] -> []
  | (lab, e)::rs -> (lab, eval e)::evalRecord rs
and eval (exp : expr) : evT =
  match exp with
  | LitInt n -> Int n
  | LitFalse -> Bool false
  | LitTrue -> Bool true
  | Add(a, b) -> (match eval a, eval b with
                  | Int n, Int m -> Int (n + m)
                  | _ -> raise TypeMismatch)
  | Record recordBody -> RecordEv (evalRecord recordBody)
  | Select(e, lab) -> (match eval e with
                        | RecordEv body -> lookupRecord body lab
                        | _ -> raise TypeMismatch)

        