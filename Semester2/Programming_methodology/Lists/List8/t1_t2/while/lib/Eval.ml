open Ast

type value =
  | VInt of Bigint.t
  | VBool of bool
  | VStr of string

module Memory : sig
  type 'a t
  val empty : 'a t
  val add : string -> 'a -> 'a t -> 'a t
  val find_opt : string -> 'a t -> 'a option
end = Map.Make(String)

type memory = value Memory.t

let rec show_value (v : value) : string =
  match v with
  | VInt a -> Bigint.to_string a
  | VBool b -> string_of_bool b
  | VStr s -> s

let print_value (v : value) : unit =
  v |> show_value |> print_string

let rec equal_value (v1 : value) (v2 : value) : bool =
  match v1, v2 with
  | VInt a1, VInt a2 -> Bigint.equal a1 a2
  | VBool a1, VBool a2 -> Bool.equal a1 a2
  | VStr a1, VStr a2 -> String.equal a1 a2
  | _ -> false

let eval_op (op : bop) (l : value) (r : value) : value =
  match op, l, r with
  | Mult, VInt l, VInt r -> VInt (Bigint.( * ) l r)
  | Div, VInt l, VInt r -> VInt (Bigint.( / ) l r)
  | Add, VInt l, VInt r -> VInt (Bigint.( + ) l r)
  | Add, VStr l, VStr r -> VStr (l ^ r)
  | Sub, VInt l, VInt r -> VInt (Bigint.( - ) l r)
  | Eq, l, r -> VBool (equal_value l r)
  | Neq, l, r -> VBool (equal_value l r |> not)
  | Gt, VInt l, VInt r -> VBool (Bigint.compare l r > 0)
  | Geq, VInt l, VInt r -> VBool (Bigint.compare l r >= 0)
  | Lt, VInt l, VInt r -> VBool (Bigint.compare l r < 0)
  | Leq, VInt l, VInt r -> VBool (Bigint.compare l r <= 0)
  | _ -> failwith "type error"

let rec eval (e : expr) (m : memory) : value =
  match e with
  | Int a -> VInt (Bigint.of_int a)
  | Bool b -> VBool b
  | Str s -> VStr s
  | Binop (op, l, r) -> eval_op op (eval l m) (eval r m)
  | Var x ->
      begin match Memory.find_opt x m with
      | Some v -> v
      | None -> VInt (Bigint.of_int 0) (* wartość domyślna *)
      end

let rec exec (s : stmt) (m : memory) : memory =
  match s with
  | Assign (x, e) ->
      let v = eval e m in
      Memory.add x v m
  | Skip -> m
  | Cmp (s1, s2) ->
      m |> exec s1 |> exec s2
  | Print e ->
      let v = eval e m in
      print_value v;
      flush stdout;
      Unix.sleep 1;
      m
  | If (p, t, e) ->
      let v = eval p m in
      (match v with
       | VBool true -> exec t m
       | VBool false -> exec e m
       | _ -> failwith "type error")
  | While (p, b) ->
      let v = eval p m in
      (match v with
       | VBool false -> m
       | VBool true -> exec b m |> exec s
       | _ -> failwith "type error")

let parse (s : string) : stmt =
  Parser.main Lexer.read (Lexing.from_string s)

let interp (s : string) : unit =
  ignore (exec (parse s) Memory.empty)
