open Ast

type value =
  | VInt of int
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
  | VInt a -> string_of_int a
  | VBool b -> string_of_bool b
  | VStr s -> s

let print_value (v : value) : unit =
  v |> show_value |> print_string

let rec equal_value (v1 : value) (v2 : value) : bool =
  match v1, v2 with
  | VInt a1, VInt a2 -> Int.equal a1 a2
  | VBool a1, VBool a2 -> Bool.equal a1 a2
  | VStr a1, VStr a2 -> String.equal a1 a2
  | _ -> false

let eval_op (op : bop) (l : value) (r : value) : value =
  match op, l, r with
  | Mult, VInt l, VInt r -> VInt (l * r)
  | Div, VInt l, VInt r -> VInt (l / r)
  | Add, VInt l, VInt r -> VInt (l + r)
  | Add, VStr l, VStr r -> VStr (l ^ r)
  | Sub, VInt l, VInt r -> VInt (l - r)
  | Eq, l, r -> VBool (equal_value l r)
  | Neq, l, r -> VBool (equal_value l r |> not)
  | Gt, VInt l, VInt r -> VBool (l > r)
  | Geq, VInt l, VInt r -> VBool (l >= r)
  | Lt, VInt l, VInt r -> VBool (l < r)
  | Leq, VInt l, VInt r -> VBool (l <= r)
  | _ -> failwith "type error"

let rec eval (e : expr) (m : memory) : value =
  match e with
  | Int a -> VInt a
  | Bool b -> VBool b
  | Str s -> VStr s
  | Binop (op, l, r) -> eval_op op (eval l m) (eval r m)
  | Var x ->
      begin match Memory.find_opt x m with
      | Some v -> v
      | None -> VInt 0 (* wartość domyślna *)
      end

let rec exec (s : stmt) (m : memory) : (memory * bool) =
  begin match s with
  | Assign (x, e) ->
      let v = eval e m in
      (Memory.add x v m, true)
  | AssignMult (x, e) ->
      let x_v = eval (Var x) m in
      let e_v = eval e m in
      (Memory.add x (eval_op Mult x_v e_v) m, true)
  | AssignDiv (x, e) ->
      let x_v = eval (Var x) m in
      let e_v = eval e m in
      (Memory.add x (eval_op Div x_v e_v) m, true)
  | AssignSub (x, e) ->
      let x_v = eval (Var x) m in
      let e_v = eval e m in
      (Memory.add x (eval_op Sub x_v e_v) m, true)
  | AssignAdd (x, e) ->
      let x_v = eval (Var x) m in
      let e_v = eval e m in
      (Memory.add x (eval_op Add x_v e_v) m, true)
  | Skip -> (m, true)
  | Halt -> (m, false)
  | Cmp (s1, s2) ->
      let (new_mem, cont) = exec s1 m in
      if cont then exec s2 new_mem else (new_mem, false)
  | Print e ->
      let v = eval e m in
      print_value v;
      (m, true)
  | If (p, t, e) ->
      let v = eval p m in
      (match v with
      | VBool true -> exec t m
      | VBool false -> exec e m
      | _ -> failwith "type error")
  | While (p, b) ->
      let v = eval p m in
      (match v with
      | VBool false -> (m, true)
      | VBool true -> 
          let (new_mem, cont) = exec b m in
          if cont then exec s new_mem else (new_mem, false)
      | _ -> failwith "type error") end

let parse (s : string) : stmt =
  Parser.main Lexer.read (Lexing.from_string s)

let interp (s : string) : unit =
  ignore (exec (parse s) Memory.empty)

let print_bop (b : bop) : string =
  match b with
  | Mult -> "*"
  | Div -> "/"
  | Add -> "+"
  | Sub -> "-"
  | Eq -> "=="
  | Neq -> "<>"
  | Gt -> ">"
  | Geq -> ">="
  | Lt -> "<"
  | Leq -> "<="

let add_paren (s : string) = "(" ^ s ^ ")"

let prio (b : bop) : int =
  match b with
  | Mult | Div -> 4
  | Add | Sub -> 3
  | Gt | Geq | Lt | Leq -> 2
  | Eq | Neq -> 1

let pretty_print_expr (e : Ast.expr) : string =
  let rec aux e inner =
    match e with
    | Int i -> string_of_int i
    | Bool b -> string_of_bool b
    | Str s -> s
    | Binop (b, e1, e2) -> 
        let s = (aux e1 true) ^ " " ^ (print_bop b) ^ " " ^ (aux e2 true) in
        if inner then add_paren s else s
    | Var x -> x
  in aux e false

let pretty_print_expr_v2 (e : Ast.expr) : string =
  let rec aux e par_prio is_right =
    match e with
    | Int i -> string_of_int i
    | Bool b -> string_of_bool b
    | Str s -> s
    | Binop (b, e1, e2) ->
        let curr_prio = prio b in
        let left = aux e1 curr_prio false in
        let right = aux e2 curr_prio true in
        let s = left ^ " " ^ (print_bop b) ^ " " ^ right in
        if (par_prio > curr_prio || (par_prio = curr_prio && is_right)) then add_paren s else s
    | Var x -> x
  in aux e 0 false

let rec pretty_print (s : Ast.stmt) (lvl : int) : string =
  let indent lvl =
    let rec spaces n = if n <= 0 then "" else " " ^ spaces (n - 1)
    in spaces (lvl * 2)
  in

  match s with
  | Assign (x, e) -> (indent lvl) ^ Printf.sprintf "%s = %s;" x (pretty_print_expr_v2 e)
  | AssignMult (x, e) -> (indent lvl) ^ Printf.sprintf "%s *= %s;" x (pretty_print_expr_v2 e)
  | AssignDiv (x, e) -> (indent lvl) ^ Printf.sprintf "%s /= %s;" x (pretty_print_expr_v2 e)
  | AssignAdd (x, e) -> (indent lvl) ^ Printf.sprintf "%s += %s;" x (pretty_print_expr_v2 e)
  | AssignSub (x, e) -> (indent lvl) ^ Printf.sprintf "%s -= %s;" x (pretty_print_expr_v2 e)
  | Skip -> (indent lvl) ^ "skip;"
  | Halt -> (indent lvl) ^ "halt;"
  | Print e -> (indent lvl) ^ Printf.sprintf "print(%s);" (pretty_print_expr_v2 e)
  | If (p, t, e) ->
      (indent lvl) ^ "if (" ^ (pretty_print_expr_v2 p) ^ ")\n"
      ^ (indent lvl) ^ "{\n"
      ^ (pretty_print t (lvl + 1)) ^ "\n"
      ^ indent lvl ^ "}\n"
      ^ (indent lvl) ^ "else\n"
      ^ (indent lvl) ^ "{\n"
      ^ (pretty_print e (lvl + 1)) ^ "\n"
      ^ indent lvl ^ "}"
  | While (p, b) -> 
      (indent lvl) ^ "while (" ^ (pretty_print_expr_v2 p) ^ ")\n"
      ^ (indent lvl) ^ "{\n"
      ^ (pretty_print b (lvl + 1)) ^ "\n"
      ^ indent lvl ^ "}"
  | Cmp (s1, s2) ->
      let rec flatten st =
        begin match st with
        | Cmp (s1, s2) -> flatten s1 @ flatten s2
        | st -> [st] end
      in 
      let flattened = flatten s in
      let stmts = List.map (fun st -> pretty_print st (lvl + 1)) flattened in
      (indent lvl) ^ "{\n"
      ^ String.concat "\n" stmts
      ^ "\n" ^ (indent lvl) ^ "}"