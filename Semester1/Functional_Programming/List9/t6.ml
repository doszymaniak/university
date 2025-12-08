module QBF = struct
  type var = string
  type formula =
  | Var of var
  | Bot
  | Not of formula
  | And of formula * formula
  | All of var * formula
end

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

type 'v env = QBF.var -> 'v

let rec scope_check : type v. v env -> QBF.formula -> v NestedQBF.formula =
  fun vars f ->
    match f with
    | QBF.Var v -> NestedQBF.Var (vars v)
    | QBF.Bot -> NestedQBF.Bot
    | QBF.Not f -> NestedQBF.Not (scope_check vars f)
    | QBF.And (f1, f2) -> NestedQBF.And (scope_check vars f1, scope_check vars f2)
    | QBF.All (v, f) ->
        let new_vars x = if x = v then NestedQBF.Z else NestedQBF.(S (vars x)) in
        NestedQBF.All (scope_check new_vars f)

let transform : QBF.formula -> 'v NestedQBF.formula =
  fun f -> scope_check (fun x -> failwith "Empty variable!") f

let ex1 = QBF.All ("p", QBF.Not (QBF.And (QBF.Var "p", QBF.Not (QBF.Var "p"))))
let ex2 = QBF.All ("p", QBF.All ("q", QBF.And (QBF.Var "p", QBF.Var "q")))