{
  open Parser

  exception Error of char
}

let white = [' ' '\t' '\n']+
let digit = ['0'-'9']
let number = digit+
let id_start = ['a'-'z' 'A'-'Z' '_']
let ident  = id_start (id_start | digit)*

rule read =
  parse
  | white { read lexbuf }
  | "true" { TRUE }
  | "false" { FALSE }
  | "if" { IF }
  | "then" { THEN }
  | "else" { ELSE }
  | "let" { LET }
  | "while" { WHILE }
  | "do" { DO }
  | "done" { DONE }
  | "in"  { IN  }
  | "not" { NOT }
  | "and" { AND }
  | "or" { OR }
  | "&&" { AND }
  | "||" { OR }
  | "*" { MULT }
  | "+" { ADD }
  | "-" { SUB }
  | "/" { DIV }
  | "=" { EQ  }
  | "<" { LT }
  | ">" { GT }
  | "<=" { LEQ }
  | ">=" { GEQ }
  | "<>" { NEQ }
  | "==" { EQEQ }
  | ":=" { ASSIGN }
  | number as x { INT (int_of_string x) }
  | ident as x  { IDENT x }
  | "(" { LPAR }
  | ")" { RPAR }
  | eof { EOF }
  | _ as c { raise (Error c) }
