open VM

let rec eval code stack =
  match code, stack with
  | [], n :: _ -> n
  | MConst n :: code, _ -> eval code (n :: stack)
  | MGetLocal n :: code, _ ->
    eval code (List.nth stack n :: stack)
  | MPopLocal :: code, n :: _ :: stack ->
    eval code (n :: stack)
  | MAdd :: code, n2 :: n1 :: stack ->
    eval code ((n1 + n2) :: stack)
  | MSub :: code, n2 :: n1 :: stack ->
    eval code ((n1 - n2) :: stack)
  | MMul :: code, n2 :: n1 :: stack ->
    eval code ((n1 * n2) :: stack)
  | MDiv :: code, n2 :: n1 :: stack ->
    eval code ((n1 / n2) :: stack)
  | _ -> failwith "Runtime error"

let run (code : instr list) : int =
  eval code []

(* Zadanie 1 *)
let rec max_stack_dep code curr_dep max_dep =
  match code with
  | [] -> max_dep
  | MConst n :: r
  | MGetLocal n :: r -> 
      let curr_dep = curr_dep + 1 in
      let max_dep = max curr_dep max_dep in
      max_stack_dep r curr_dep max_dep
  | MPopLocal :: r
  | MAdd :: r
  | MSub :: r
  | MMul :: r
  | MDiv :: r ->
      max_stack_dep r (curr_dep - 1) max_dep
