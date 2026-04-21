open Ast

module Env : sig
  type 'a t
  val empty : 'a t
  val add : string -> 'a -> 'a t -> 'a t
  val find_opt : string -> 'a t -> 'a option
end = Map.Make(String)

type env = value Env.t

and value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value
  | VClosure of env * ident * expr
  | VRecClosure of env * ident * ident * expr

let rec show_value (v : value) : string =
  match v with
  | VInt a -> string_of_int a
  | VBool b -> string_of_bool b
  | VUnit -> "()"
  | VPair (v1, v2) -> Printf.sprintf "(%s,%s)" (show_value v1) (show_value v2)
  | VClosure _ | VRecClosure _ -> "<fun>"

let print_value (v : value) : unit =
  v |> show_value |> print_endline

let rec equal_value (v1 : value) (v2 : value) : bool =
  match v1, v2 with
  | VInt a1, VInt a2 -> Int.equal a1 a2
  | VBool a1, VBool a2 -> Bool.equal a1 a2
  | VUnit, VUnit -> true
  | VPair (a1, a2), VPair (b1, b2) -> equal_value a1 b1 && equal_value a2 b2
  | _ -> false

let eval_op (op : bop) (l : value) (r : value) : value =
  match op, l, r with
  | Mult, VInt l, VInt r -> VInt (l * r)
  | Div, VInt l, VInt r  -> VInt (l / r)
  | Add, VInt l, VInt r  -> VInt (l + r)
  | Sub, VInt l, VInt r  -> VInt (l - r)
  | Eq, l, r -> VBool (equal_value l r)
  | Neq, l, r -> VBool (equal_value l r |> not)
  | Gt, VInt l, VInt r -> VBool (l > r)
  | Geq, VInt l, VInt r -> VBool (l >= r)
  | Lt, VInt l, VInt r -> VBool (l < r)
  | Leq, VInt l, VInt r -> VBool (l <= r)
  | _ -> failwith "type error"

let rec eval (env : env) (e : expr) : value =
  match e with
  | Int a -> VInt a
  | Binop (op, l, r) -> eval_op op (eval env l) (eval env r)
  | Bool b -> VBool b
  | If (b, t, e) ->
      (match eval env b with
        | VBool true -> eval env t
        | VBool false -> eval env e
        | _ -> failwith "type error")
  | Unit -> VUnit
  | Pair (e1, e2) -> VPair (eval env e1, eval env e2)
  | Match (e1, x, y, e2) ->
      (match eval env e1 with
        | VPair (v1, v2) ->
            let env' = env |> Env.add x v1 |> Env.add y v2 in
            eval env' e2
        | _ -> failwith "type error")
  | Let (x, e1, e2) ->
      let v1 = eval env e1 in
      let env' = Env.add x v1 env in
      let v2 = eval env' e2 in
      v2
  | Var y ->
      (match Env.find_opt y env with
       | Some v -> v
       | None -> failwith ("unknown var " ^ y))
  | Fun (x, e) -> VClosure (env, x, e)
  | Funrec (f, x, e) -> VRecClosure (env, f, x, e)
  | App (e1, e2) ->
      (match eval env e1 with
        | VClosure (env', x, body) ->
            let v_arg = eval env e2 in
            eval (Env.add x v_arg env') body
        | VRecClosure (env', f, x, body) as c ->
            let v_arg = eval env e2 in
            let env'' = env' |> Env.add x v_arg |> Env.add f c in
            eval env'' body
        | _ -> failwith "type error")

let rec free_vars (e : Ast.expr) : Ast.ident list =
  let rec aux bound_list e =
    match e with
    | Int _ | Bool _ | Unit -> []
    | Binop (_, e1, e2) | App (e1, e2) | Pair (e1, e2) -> 
        (aux bound_list e1) @ (aux bound_list e2)
    | If (e1, e2, e3) ->
        (aux bound_list e1) @ (aux bound_list e2) @ (aux bound_list e3)
    | Match (e1, i1, i2, e2) ->
        (aux bound_list e1) @ (aux (i1 :: i2 :: bound_list) e2)
    | Let (i, e1, e2) -> (aux bound_list e1) @ (aux (i :: bound_list) e2)
    | Var x -> if List.mem x bound_list then [] else [x]
    | Fun (i, e) -> aux (i :: bound_list) e
    | Funrec (f, i, e) -> aux (f :: i :: bound_list) e
  in List.sort_uniq String.compare (aux [] e)

let interp (env : env) (s : string) : value =
  let ast =
    Parser.main Lexer.read (Lexing.from_string s)
  in
  let free = free_vars ast in
  if List.length free > 0 then
  (
    Printf.printf "Undeclared variables: \n";
    List.iter (fun x -> Printf.printf "%s " x) free;
    Printf.printf "\n";
  );
  eval env ast

let eval_def (env : env) ((x, e) : def) : env =
  let v = eval env e in
  print_endline x;
  Env.add x v env

let eval_prog (env : env) (s : def list) : env =
  List.fold_left eval_def env s

let interp_prog (env : env) (s : string) : env =
  let defs =
    Parser.program Lexer.read (Lexing.from_string s)
  in
  eval_prog env defs

let rec alpha_equiv (e1 : expr) (e2 : expr) : bool =
  let rec aux env1 env2 e1 e2 =
    match e1, e2 with
    | Int a, Int b -> a = b
    | Bool a, Bool b -> a = b
    | Unit, Unit -> true
    | Var x, Var y ->
        begin match Env.find_opt x env1, Env.find_opt y env2 with
        | Some y', Some x' -> x = x' && y = y'
        | None, None -> x = y
        | _ -> false end
    | Binop (op1, l1, r1), Binop (op2, l2, r2) ->
        op1 = op2 && (aux env1 env2 l1 l2) && (aux env1 env2 r1 r2)
    | If (f1, s1, t1), If (f2, s2, t2) ->
        (aux env1 env2 f1 f2) && (aux env1 env2 s1 s2) && (aux env1 env2 t1 t2)
    | Pair (l1, r1), Pair (l2, r2) ->
        (aux env1 env2 l1 l2) && (aux env1 env2 r1 r2)
    | Match (e1, x1, y1, e11), Match (e2, x2, y2, e22) ->
        (aux env1 env2 e1 e2) &&
        (
          let new_env1 = env1 |> Env.add x1 x2 |> Env.add y1 y2 in
          let new_env2 = env2 |> Env.add x2 x1 |> Env.add y2 y1 in
          aux new_env1 new_env2 e11 e22
        )
    | Let (x1, e1, e11), Let (x2, e2, e22) ->
        (aux env1 env2 e1 e2) &&
        (
          let new_env1 = Env.add x1 x2 env1 in
          let new_env2 = Env.add x2 x1 env2 in
          (aux new_env1 new_env2 e11 e22)
        )
    | Fun (x1, e1), Fun (x2, e2) ->
        let new_env1 = Env.add x1 x2 env1 in
        let new_env2 = Env.add x2 x1 env2 in
        aux new_env1 new_env2 e1 e2
    | Funrec (f1, x1, e1), Funrec (f2, x2, e2) ->
        let new_env1 = env1 |> Env.add f1 f2 |> Env.add x1 x2 in
        let new_env2 = env2 |> Env.add f2 f1 |> Env.add x2 x1 in
        aux new_env1 new_env2 e1 e2
    | App (e1, e11), App (e2, e22) ->
        (aux env1 env2 e1 e2) && (aux env1 env2 e11 e22)
    | _ -> false
  in aux Env.empty Env.empty e1 e2