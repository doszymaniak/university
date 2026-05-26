open VM

module Env : sig
  type t

  val empty    : t
  val add      : t -> Ast.var -> t
  val push_tmp : t -> t
  val lookup   : t -> Ast.var -> int
end = struct
  type t = Ast.var option list

  let empty     = []
  let add env x = Some x :: env
  let push_tmp env = None :: env

  let lookup env x =
    match List.find_index (fun y -> y = Some x) env with
    | Some i -> i
    | None   -> failwith ("Unbound variable " ^ x)
end

let compile_op (op : Ast.bop) =
  match op with
  | Add  -> [ MAdd ]
  | Sub  -> [ MSub ]
  | Div  -> [ MDiv ]
  | Mult -> [ MMul ]

let rec compile env (e : Ast.expr) =
  match e with
  | Var x -> [ MGetLocal (Env.lookup env x) ]
  | Int n -> [ MConst n ]
  | Binop(op, e1, e2) ->
    compile env e1 @
    compile (Env.push_tmp env) e2 @
    compile_op op
  | Let(x, e1, e2) ->
    compile env e1 @
    compile (Env.add env x) e2 @
    [ MPopLocal ]

let compile_program e =
  compile Env.empty e

(* Zadanie 3 *)
let rec compile_opt env (e : Ast.expr) to_add =
  match e with
  | Var x -> MGetLocal (Env.lookup env x) :: to_add
  | Int n -> MConst n :: to_add
  | Binop (op, e1, e2) ->
      let code1 = compile_opt (Env.push_tmp env) e2 (compile_op op @ to_add) in
      compile_opt env e1 code1
  | Let (x, e1, e2) ->
      let code1 = compile_opt (Env.add env x) e2 (MPopLocal :: to_add) in
      compile_opt env e1 code1

let compile_program_opt e =
  compile_opt Env.empty e []