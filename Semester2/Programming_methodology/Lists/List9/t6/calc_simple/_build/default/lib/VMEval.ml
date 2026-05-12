open VM

let rec eval code stack =
  match code, stack with
  | [], n :: _ -> n
  | MConst n :: code, _ -> eval code (n :: stack)
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
