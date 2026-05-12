open VM
open Ast

let rec decompile code stack =
  match code, stack with
  | [], expr :: _ -> expr
  | MConst n :: code, _ -> decompile code (Int n :: stack)
  | MAdd :: code, n2 :: n1 :: stack -> decompile code (Binop (Add, n1, n2) :: stack)
  | MSub :: code, n2 :: n1 :: stack -> decompile code (Binop (Sub, n1, n2) :: stack)
  | MMul :: code, n2 :: n1 :: stack -> decompile code (Binop (Mult, n1, n2) :: stack)
  | MDiv :: code, n2 :: n1 :: stack -> decompile code (Binop (Div, n1, n2) :: stack)
  | _ -> failwith "invalid code!"

let run_decompile code = decompile code []