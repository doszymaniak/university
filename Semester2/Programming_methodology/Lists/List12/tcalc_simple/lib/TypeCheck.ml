type tp = Ast.tp =
  | TInt
  | TBool
  | TArrow of tp * tp
  | TPair  of tp * tp
  | TUnit
  | TRef of tp

let paren prec p str =
  if prec > p then "(" ^ str ^ ")"
  else str

let rec pretty_tp prec tp =
  match tp with
  | TInt  -> "int"
  | TBool -> "bool"
  | TArrow(tp1, tp2) ->
    paren prec 0 (pretty_tp 1 tp1 ^ " -> " ^ pretty_tp 0 tp2)
  | TPair(tp1, tp2) ->
    paren prec 10
      (pretty_tp 10 tp1 ^ " * " ^ pretty_tp 11 tp2)
  | TUnit -> "unit"
  (* ref z najwyzszym wiazaniem, przykleja sie do najblizszego typu *)
  | TRef tp1 -> paren prec 20 (pretty_tp 21 tp1 ^ " ref")

let string_of_tp tp =
  pretty_tp 0 tp

module Env : sig
  type t

  val empty : t

  val add_var : t -> Ast.var -> tp -> t
  val add_vars : t -> (Ast.var * tp) list -> t

  val lookup_var : t -> Ast.var -> tp option
end = struct
  module StrMap = Map.Make(String)

  type t = tp StrMap.t

  let empty = StrMap.empty

  let add_var env x tp =
    StrMap.add x tp env

  let add_vars =
    List.fold_left (fun env (x, tp) -> add_var env x tp)

  let lookup_var env x =
    StrMap.find_opt x env
end

type loc = Lexing.position * Lexing.position
exception Type_error of loc * string

let op_type (op : Ast.bop) =
  match op with
  | Mult | Div | Add | Sub ->
    (TInt, TInt, TInt)
  | Eq | Neq | Lt | Leq | Gt | Geq ->
    (TInt, TInt, TBool)

let rec infer_type env (e : Ast.expr) =
  let loc = e.loc in
  match e.data with
  | Var  x ->
    begin match Env.lookup_var env x with
    | Some tp -> tp
    | None    ->
      raise (Type_error(loc, "Unbound variable " ^ x))
    end
  | Int  _ -> TInt
  | Bool _ -> TBool
  | And(e1, e2) ->
    check_type env e1 TBool;
    check_type env e2 TBool;
    TBool
  | Not  e ->
    check_type env e TBool;
    TBool
  | If(e1, e2, e3) ->
    check_type env e1 TBool;
    let tp = infer_type env e2 in
    check_type env e3 tp;
    tp
  | Binop(op, e1, e2) ->
    let (tp1, tp2, tp) = op_type op in
    check_type env e1 tp1;
    check_type env e2 tp2;
    tp
  | Let(x, e1, e2) ->
    let tp1 = infer_type env e1 in
    infer_type (Env.add_var env x tp1) e2
  | Fun(x, tp, e) ->
    TArrow(tp, infer_type (Env.add_var env x tp) e)
  | App(e1, e2) ->
    begin match infer_type env e1 with
    | TArrow(tp2, tp1) ->
      check_type env e2 tp2;
      tp1
    | tp ->
      raise (Type_error(e1.loc,
        "not a function: " ^ string_of_tp tp))
    end
  | Pair(e1, e2) ->
    TPair(infer_type env e1, infer_type env e2)
  | Fst e ->
    begin match infer_type env e with
    | TPair(tp1, tp2) -> tp1
    | tp ->
      raise (Type_error(e.loc,
        "not a pair: " ^ string_of_tp tp))
    end
  | Snd e ->
    begin match infer_type env e with
    | TPair(tp1, tp2) -> tp2
    | tp ->
      raise (Type_error(e.loc,
        "not a pair: " ^ string_of_tp tp))
    end
  | Unit -> TUnit
  | Ref e -> TRef (infer_type env e)
  | Deref e ->
      begin match infer_type env e with
      | TRef tp -> tp
      | tp -> raise (Type_error (e.loc, "not a ref: " ^ string_of_tp tp)) end
  | Assign (e1, e2) ->
      begin match infer_type env e1 with
      | TRef tp -> check_type env e2 tp; TUnit
      | tp -> raise (Type_error (e1.loc, "not a ref: " ^ string_of_tp tp)) end


and check_type env e tp =
  let tp' = infer_type env e in
  if tp' <> tp then
    raise (Type_error(e.loc,
      ("type error: got: " ^ string_of_tp tp' ^
      " expected: " ^ string_of_tp tp)))

let check_program prog =
  let _ = infer_type Env.empty prog in
  prog
