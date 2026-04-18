{
  open Parser
}

let white = [' ' '\t' '\n']+
let digit = ['0'-'9']
let number = digit+
let ident = ['a'-'z' 'A'-'Z']['a'-'z' 'A'-'Z' '0'-'9']*

rule read =
  parse
  | white { read lexbuf }
  | "true" { TRUE }
  | "false" { FALSE }
  | "if" { IF }
  | "then" { THEN }
  | "else" { ELSE }
  | "let" { LET }
  | "fst" { FST }
  | "snd" { SND }
  | "match" { MATCH }
  | "with" { WITH }
  | "sum" { SUM }
  | "to" { TO }
  | "in" { IN }
  | "=" { EQ }
  | "in" { IN }
  | "*" { MULT }
  | "+" { ADD }
  | "-" { SUB }
  | "/" { DIV }
  | number { INT (Lexing.lexeme lexbuf
                  |> int_of_string) }
  | ident { IDENT (Lexing.lexeme lexbuf) }
  | "(" { LPAR }
  | ")" { RPAR }
  | "," { COMMA }
  | "->" { ARROW }
  | ident { IDENT (Lexing.lexeme lexbuf) }
  | number { INT (Lexing.lexeme lexbuf
                  |> int_of_string) }
  | eof { EOF }
