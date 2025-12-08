module NestedQBF = struct
  type empty = |
  type 'v inc = Z | S of 'v
  type 'v formula =
  | Var of 'v
  | Bot
  | Not of 'v formula
  | And of 'v formula * 'v formula
  | All of 'v inc formula 
end

open NestedQBF

let absurd (x : empty) = match x with | _ -> .

type 'v env = 'v -> bool

let rec eval : type v. v env -> v formula -> bool =
  fun vars f ->
    match f with
    | Var v -> vars v
    | Bot -> false
    | Not f' -> not (eval vars f')
    | And (f1, f2) -> (eval vars f1) && (eval vars f2)
    | All f' ->
        let vars_true x =
          match x with
          (* The variable bound by the current quantifier *)
          | Z -> true
          (* A variable from the outer scope *)
          | S x -> vars x
        in
        let vars_false x =
          match x with
          | Z -> false
          | S x -> vars x
        in (eval vars_true f') && (eval vars_false f')

let is_true : empty formula -> bool =
  fun f -> eval absurd f

let ex = All (And (Var Z, All (And (Var (S Z), Var Z))))