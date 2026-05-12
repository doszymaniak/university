open VM

let compile_op (op : Ast.bop) =
  match op with
  | Add  -> [ MAdd ]
  | Sub  -> [ MSub ]
  | Div  -> [ MDiv ]
  | Mult -> [ MMul ]

let rec compile (e : Ast.expr) =
  match e with
  | Int n -> [ MConst n ]
  | Binop(op, e1, e2) ->
    compile e1 @ compile e2 @ compile_op op
