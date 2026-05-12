
(* The type of tokens. *)

type token = 
  | SUB
  | RPAR
  | MULT
  | LPAR
  | INT of (int)
  | EOF
  | DIV
  | ADD

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val main: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.expr)
