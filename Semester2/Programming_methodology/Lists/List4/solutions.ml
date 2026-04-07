type 'v nnf =
| NNFLit of bool * 'v
| NNFConj of 'v nnf * 'v nnf
| NNFDisj of 'v nnf * 'v nnf

type 'v formula =
| Var of 'v
| Neg of 'v formula
| Conj of 'v formula * 'v formula
| Disj of 'v formula * 'v formula


(* Task 4 *)
let rec neg_nnf f =
  match f with
  | NNFLit (p, x) -> NNFLit(not p, x)
  | NNFConj (l, r) -> NNFDisj(neg_nnf l, neg_nnf r)
  | NNFDisj (l, r) -> NNFConj(neg_nnf l, neg_nnf r)


(* Task 5 *)
let rec eval_nnf sigma f =
  match f with
  | NNFLit (true, x) -> sigma x
  | NNFLit (false, x) -> not (sigma x)
  | NNFConj (l, r) -> (eval_nnf sigma l) && (eval_nnf sigma r)
  | NNFDisj (l, r) -> (eval_nnf sigma l) || (eval_nnf sigma r)


(* Task 6 *)
let rec to_nnf f =
  match f with
  | Var x -> NNFLit(true, x)
  | Neg x -> neg_nnf (to_nnf x)
  | Conj (f1, f2) -> NNFConj (to_nnf f1, to_nnf f2)
  | Disj (f1, f2) -> NNFDisj (to_nnf f1, to_nnf f2)
and neg_nnf f =
  match f with
  | NNFLit (p, x) -> NNFLit(not p, x)
  | NNFConj (l, r) -> NNFDisj(neg_nnf l, neg_nnf r)
  | NNFDisj (l, r) -> NNFConj(neg_nnf l, neg_nnf r)

let rec to_nnf f =
  match f with
  | Var v -> NNFLit (false, v)
  | Conj (f1, f2) -> NNFConj (to_nnf f2, to_nnf f2)
  | Disj (f1, f2) -> NNFDisj (to_nnf f1, to_nnf f2)
  | Neg f -> to_nnf_neg f1
and to_nnf_neg f =
  | Var v -> NNFLit (true, v)
  | Conj (f1, f2) -> NNFDisj (to_nnf_neg f1, to_nnf_neg f2)
  | Disj (f1, f2) -> NNFConj (to_nnf_neg f1, to_nnf_neg f2)
  | Neg f -> to_nnf f


(* Task 7 *)
let rec eval_formula sigma f =
  match f with
  | Var x -> sigma x
  | Neg x -> not (eval_formula sigma x)
  | Conj (l, r) -> (eval_formula sigma l) && (eval_formula sigma r)
  | Disj (l, r) -> (eval_formula sigma l) || (eval_formula sigma r)


(* Task 8 *)
let rec is_sorted l = 
  match l with
  | [] | [_] -> true
  | x :: y :: xs -> x <= y && (is_sorted (y :: xs))

let rec insert el l =
  match l with
  | [] -> [el]
  | x :: xs -> 
      if el <= x then el :: x :: xs
      else x :: (insert el xs)