module QBF = struct
  type var = string
  type formula =
  | Var of var
  | Bot
  | Not of formula
  | And of formula * formula
  | All of var * formula
end

open QBF

type env = var -> bool

let rec eval : env -> formula -> bool =
  fun vars f ->
    match f with
    | Var v -> vars v
    | Bot -> false
    | Not f' -> not (eval vars f')
    | And (f1, f2) -> (eval vars f1) && (eval vars f2)
    | All (v, f') ->
        (* We consider both possible assignments of v: true and false *)
        let vars_true x = if x = v then true else vars x in
        let vars_false x = if x = v then false else vars x in
        (eval vars_true f') && (eval vars_false f')

let is_true : formula -> bool =
  fun f -> eval (fun x -> failwith "Free variable!") f

let taut = All ("p", Not (And (Var "p", Not (Var "p"))))
let not_taut = All ("p", All ("q", And (Var "p", Var "q")))