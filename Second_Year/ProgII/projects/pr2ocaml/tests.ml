open Interpreter
open Typechecker

let empty_set_int = EmptySet(IntTy)
let empty_set_bool = EmptySet(BoolTy)
let set_int1 = Singleton(IntTy, LitInt 5)
let set_int2 = Of(IntTy, Cons(LitInt 3, Cons(LitInt 5, Cons(LitInt 8, Empty))))
          (* = Of(IntTy, LitInt 3 @: LitInt 5 @: LitInt 8 @: Empty) *)
let set_int3 = Of(IntTy, LitInt 2 @: LitInt 3 @: LitInt 8 @: Empty)
let wrong_set = Of(IntTy, LitInt 2 @: LitStr "a" @: LitInt 3 @: Empty)
let set_string = Of(StrTy, LitStr "a" @: LitStr "b" @: LitStr "ciao" @: Empty)

(* Testing eval *)

(*  Base operations *)
let union = Union(set_int1, set_int3)
  (* => {2, 3, 5, 8} *)
let union_wrong = Union(set_int1, set_string)
  (* error *)
let union_wrong2 = Union(LitInt 4, set_string)

let inters = Inters(set_int2, set_int3)
  (* => {3, 8} *)
let inters_wrong = Inters(set_int1, set_string)
  (* error *)

let diff1 = SetDiff(set_int3, set_int2)
  (* => {2} *)
let diff2 = SetDiff(set_int3, set_int1)
  (* => {2, 3, 8} *)
let diff_wrong = SetDiff(set_string, set_int1)
  (* error *)  

let insert1 = Insert(LitInt 4, set_int3)
  (* => {2, 3, 4, 8} *)
let insert2 = Insert(LitStr "ciao", set_string)
  (* => {"a", "b", "ciao"} *)
let insert_wrong = Insert(LitInt 4, set_string)
  (* error *)

let remove1 = Remove(LitInt 4, set_int3)
  (* => {2, 3, 8} *)
let remove2 = Remove(LitStr "ciao", set_string)
  (* => {"a", "b"} *)

let contains1 = Contains(LitInt 4, set_int3)
  (* => Bool false *)
let contains2 = Contains(LitStr "ciao", set_string)
  (* => Bool true*)

let subset1 = Subset(set_int1, set_int2)
  (* => Bool true *)
let subset2 = Subset(set_int1, set_int3)
  (* => Bool false *)
let subset_wrong = Subset(set_int1, set_string)
  (* error *)

let is_empty1 = IsEmpty(empty_set_bool)
  (* => Bool true *)
let is_empty2 = IsEmpty(set_int1)
  (* => Bool false *)

let min1 = MinOf(set_int2)
  (* => Int 3 *)
let min2 = MinOf(set_string)
  (* => Str "a" *)

let max1 = MaxOf(set_int2)
  (* => Int 8 *)
let max2 = MaxOf(set_string)
  (* => Str "ciao" *)

(* Functional operators *)
let pred_int_t = Fun("x", LitTrue, IntTy, BoolTy)
  (* ~> (fun x -> true) *)
let pred_int_f = Fun("x", LitFalse, IntTy, BoolTy)
  (* ~> (fun x -> false) *)
let pred_int1 = Fun("x", IsZero(Sub (Den "x", LitInt(-3))), IntTy, BoolTy)
  (* ~> (fun x -> x - 3 = 0) *)
let pred_int2 = Fun("x", Equals(LitInt 5, Den "x"), IntTy, BoolTy)
  (* ~> (fun x -> x = 5 *)
let pred_string = Fun("x", LitFalse, StrTy, BoolTy)
  (* ~> (fun x -> false) *)
let map_int_string = Fun("x", LitStr "a", IntTy, StrTy)
  (* ~> (fun x -> "a") *)
let map_int_int = Fun("x", Add(Den "x", LitInt 2), IntTy, IntTy)
  (* ~> (fun x -> x + 2) *)

let forall1 = ForAll(pred_int_t, set_int2)
  (* => Bool true *)
let forall2 = ForAll(pred_int2, set_int2)
  (* => Bool false *)
let forall3 = ForAll(pred_string, set_string)
  (* => Bool false *)
let forall_err = ForAll(pred_string, set_int1)
  (* error *)

let exists1 = Exists(pred_int_f, set_int2)
  (* => Bool false *)
let exists2 = Exists(pred_int1, set_int3)
  (* => Bool true *)
let exists3 = Exists(pred_string, set_string)
  (* => Bool false *)
let exists_err = Exists(pred_string, set_int1)
  (* error *)

let filter1 = Filter(pred_int1, set_int3)
  (* => {3} *)
let filter2 = Filter(pred_int2, set_int1)
  (* => {} *)
let filter3 = Filter(pred_string, set_string)
  (* => {} *)
let filter_err = Filter(pred_int1, set_string)
  (* error *)

let map1 = Map(map_int_string, set_int3)
  (* => {"a"} *)
let map2 = Map(map_int_int, set_int3)
  (* => {4, 5, 10} *)

let non_fun = Filter(LitInt 4, set_int1)
  (* error *)

let fact5 = 
  ( LetRec("fact", "n", IntTy, IntTy, 
    IfThenElse(
      Or(IsZero(Den "n"), Equals(Den "n", LitInt 1)), 
      LitInt 1, 
      Times(Den "n", Apply(Den "fact", Sub(Den "n", LitInt 1)))
    ), 
    Apply(Den "fact", LitInt 5)) )
  (* => 120 *)

let all_even =
  ( LetRec("isEven", "n", IntTy, BoolTy,
    IfThenElse(
      IsZero(Den "n"),
      LitTrue,
      IfThenElse(
        Equals(LitInt 1, Den "n"),
        LitFalse,
        Apply(Den "isEven", Sub(Den "n", LitInt 2))
      )
    ),
    ForAll(
      Fun("n", Apply(Den "isEven", Den "n"), IntTy, BoolTy), 
      Of(IntTy, LitInt 2 @: LitInt 4 @: LitInt 12 @: Empty))
    ) 
  )
  (* => Bool true *)

(* Static typechecker tests *)

let wrong_if = IfThenElse(LitTrue, LitFalse, LitInt 5)
  (* error: different branch types *)
let wrong_ret_ty = Fun("x", LitStr "a", IntTy, IntTy)
  (* error: wrong return type *)
let wrong_fact = 
  ( LetRec("fact", "n", IntTy, StrTy,  (* return type should be IntTy*)
    IfThenElse(
      IsZero(Den "n"), 
      LitInt 1, 
      Times(Den "n", Apply(Den "fact", Sub(Den "n", LitInt 1)))
    ), 
    Apply(Den "fact", LitInt 5)) )
  (* error *)
let wrong_apply = Apply(map_int_int, LitStr "a")
  (* error: wrong argument type *)
