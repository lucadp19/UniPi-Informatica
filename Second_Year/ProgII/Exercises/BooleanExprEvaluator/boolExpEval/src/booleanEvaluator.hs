data BooleanExpr = 
      BTrue
    | BFalse
    | Not BooleanExpr
    | And BooleanExpr BooleanExpr
    | Or BooleanExpr BooleanExpr
    | Implies BooleanExpr BooleanExpr
    | If BooleanExpr BooleanExpr BooleanExpr

eval :: BooleanExpr -> Bool
eval BTrue = True
eval BFalse = False
eval (Not exp) = not $ eval exp
eval (exp `And` exp') = eval exp && eval exp'
eval (exp `Or` exp') = eval exp || eval exp'
eval (exp `Implies` exp') = 
    case v of
        False -> True
        True  -> v'
    where v = eval exp
          v' = eval exp'
eval (If cond exp exp') = 
    case ev_cond of
        True -> eval exp
        False -> eval exp'
    where ev_cond = eval cond

