open Ast

type value =
  | VInt of int
  | VBool of bool
  | VUnit
  | VPair of value * value

let rec show_value (v : value) : string =
  match v with
  | VInt a -> string_of_int a
  | VBool b -> string_of_bool b
  | VUnit -> "()"
  | VPair (a, b) -> "(" ^ show_value a ^ ", " ^ show_value b ^ ")"

let print_value (v : value) : unit =
  v |> show_value |> print_string

let eval_op (op : bop) (l : value) (r : value) : value =
  match op, l, r with
  | Mult, VInt l, VInt r -> VInt (l * r)
  | Div, VInt l, VInt r  -> VInt (l / r)
  | Add, VInt l, VInt r  -> VInt (l + r)
  | Sub, VInt l, VInt r  -> VInt (l - r)
  | _ -> failwith "type error"

module Env : sig
  type 'a t
  val empty : 'a t
  val add : string -> 'a -> 'a t -> 'a t
  val find_opt : string -> 'a t -> 'a option
end = Map.Make(String)

type env = value Env.t

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
  | Let (x, e1, e2) ->
      let v1 = eval env e1 in
      let env' = Env.add x v1 env in
      let v2 = eval env' e2 in
      v2
  | Var y ->
      (match Env.find_opt y env with
       | Some v -> v
       | None -> failwith ("unknown var " ^ y))
  | Unit -> VUnit
  | Pair (a, b) -> VPair (eval env a, eval env b)
  | Fst e ->
      (match eval env e with
      | VPair (v1, _) -> v1
      | _ -> failwith "type error")
  | Snd e ->
      (match eval env e with
      | VPair (_, v2) -> v2
      | _ -> failwith "type error")
  | Match (e1, x, y, e2) ->
      let (v1, v2) =
        (match eval env e1 with
        | VPair (v1, v2) -> (v1, v2)
        | _ -> failwith "type error")
      in eval (Env.add x v1 (Env.add y v2 env)) e2
  | Sum (x, n, m, k) ->
      let v1 =
        (match eval env n with
        | VInt v -> v
        | _ -> failwith "type error")
      in
      let v2 =
        (match eval env m with
        | VInt v -> v
        | _ -> failwith "type error")
      in
      let rec aux i res =
        if i > v2 then res
        else 
          let curr_val = eval (Env.add x (VInt i) env) k in
          match curr_val with
          | VInt v -> aux (i + 1) (res + v)
          | _ -> failwith "type error"
      in VInt (aux v1 0)

let interp (s : string) : value =
  let ast =
    Parser.main Lexer.read (Lexing.from_string s)
  in
  eval Env.empty ast
