open Ast

module A = Map.Make(Int)

type value =
  | VInt of int
  | VBool of bool
  | VStr of string
  | VArray of value A.t

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
  | VArray a ->
      let last_idx =
        begin match A.max_binding_opt a with
        | Some (last_idx, _) -> last_idx
        | None -> -1 end
      in
      if last_idx = -1 then "[]" else
      let rec make_string_list curr_idx curr_str =
        begin match A.find_opt curr_idx a with
        | None -> 
            if curr_idx = last_idx then curr_str
            else make_string_list (curr_idx + 1) curr_str
        | Some v -> 
            let curr_str = curr_str ^ (show_value v)
            in if curr_idx = last_idx then curr_str
            else make_string_list (curr_idx + 1) (curr_str ^ "; ") end
      in "[" ^ (make_string_list 0 "") ^ "]"

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
  | Array a ->
      let rec eval_list list idx map =
        match list with
        | [] -> map
        | x :: xs ->
            let v = eval x m in
            eval_list xs (idx + 1) (A.add idx v map)
      in VArray (eval_list a 0 A.empty)
  | AssignRead (xs, i) ->
      let map =
        begin match Memory.find_opt xs m with
        | Some (VArray map) -> map
        | _ -> failwith "type error!" end
      in
      let idx =
        begin match eval i m with
        | VInt idx -> idx
        | _ -> failwith "type error!" end
      in
      begin match A.find_opt idx map with
      | Some v -> v
      | None -> VInt 0 end

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
  | AssignArray (xs, i, e) ->
      let map =
        begin match Memory.find_opt xs m with
        | Some (VArray map) -> map
        | _ -> failwith "type error!" end
      in
      let idx =
        begin match eval i m with
        | VInt idx -> idx
        | _ -> failwith "type error!" end
      in
      let v = eval e m in
      let new_map = A.add idx v map in
      Memory.add xs (VArray new_map) m

let parse (s : string) : stmt =
  Parser.main Lexer.read (Lexing.from_string s)

let interp (s : string) : unit =
  ignore (exec (parse s) Memory.empty)
