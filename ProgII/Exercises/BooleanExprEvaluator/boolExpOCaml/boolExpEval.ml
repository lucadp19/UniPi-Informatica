type boolExp =
  | True
  | False
  | Not     of boolExp
  | And     of boolExp * boolExp
  | Or      of boolExp * boolExp
  | Implies of boolExp * boolExp
  | If      of boolExp * boolExp * boolExp

let rec eval (exp : boolExp) : bool =
  match exp with
  | True -> true
  | False -> false
  | Not e -> not (eval e)
  | And (e1, e2) -> eval e1 && eval e2
  | Or (e1, e2) -> eval e1 || eval e2
  | Implies (e1, e2) -> (
      let v1 = eval e1 in
        match v1 with
        | false -> true
        | true -> eval e2
    )
  | If (cond, e1, e2) ->
      let ev_cond = eval cond in
        match ev_cond with
        | true -> eval e1
        | false -> eval e2
