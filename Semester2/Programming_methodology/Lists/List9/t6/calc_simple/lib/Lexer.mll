{
  open Parser

  exception Error of char
}

let white = [' ' '\t' '\n']+
let digit = ['0'-'9']
let number = digit+

rule read =
  parse
  | white { read lexbuf }
  | "*" { MULT }
  | "+" { ADD }
  | "-" { SUB }
  | "/" { DIV }
  | number { INT (Lexing.lexeme lexbuf
                  |> int_of_string) }
  | "(" { LPAR }
  | ")" { RPAR }
  | eof { EOF }
  | _ as c { raise (Error c) }
