%{
  open Ast

  let build_for init cond step b =
    let build_while =
      match cond, step with
      | None, Some step -> While (Bool true, Cmp (b, step))
      | None, None -> While (Bool true, b)
      | Some cond, None -> While (cond, b)
      | Some cond, Some step -> While (cond, Cmp (b, step))
    in 
    match init with
    | Some init -> Cmp (init, build_while)
    | None -> build_while
%}

%token <int> INT
%token <string> IDENT
%token <string> STRING
%token MULT DIV ADD SUB LT LEQ GT GEQ NEQ EQEQ EQ
%token LPAR RPAR LBRACE RBRACE SC LSQR RSQR
%token TRUE FALSE IF ELSE WHILE PRINT SKIP FOR
%token EOF

%start <Ast.stmt> main

%nonassoc LT LEQ GT GEQ NEQ EQEQ
%left ADD SUB
%left MULT DIV

%%

main:
  | e = stmts; EOF { e }
  ;

expr:
  | l = expr; MULT; r = expr { Binop (Mult, l, r) }
  | l = expr; DIV; r = expr { Binop (Div, l, r) }
  | l = expr; ADD; r = expr { Binop (Add, l, r) }
  | l = expr; SUB; r = expr { Binop (Sub, l, r) }
  | l = expr; LT; r = expr { Binop (Lt, l, r) }
  | l = expr; LEQ; r = expr { Binop (Leq, l, r) }
  | l = expr; GT; r = expr { Binop (Gt, l, r) }
  | l = expr; GEQ; r = expr { Binop (Geq, l, r) }
  | l = expr; NEQ; r = expr { Binop (Neq, l, r) }
  | l = expr; EQEQ; r = expr { Binop (Eq, l, r) }
  | i = INT { Int i }
  | TRUE { Bool true }
  | FALSE { Bool false }
  | s = STRING { Str s }
  | i = IDENT { Var i }
  | LPAR; e = expr; RPAR { e }
  ;

expr_list:
  | e1 = expr; SC; el = expr_list { e1 :: el }
  | e = expr { [e] }
  ;

stmt:
  | x = IDENT; EQ; e = expr; SC { Assign (x, e) }
  | IF; LPAR; p = expr; RPAR; t = stmt; ELSE; e = stmt { If (p, t, e) }
  | WHILE; LPAR; p = expr; RPAR; b = stmt { While (p, b) }
  | FOR; LPAR; init = maybe_assign; SC; cond = maybe_expr; SC; step = maybe_assign; RPAR; b = stmt { build_for init cond step b }
  | PRINT; LPAR; e = expr; RPAR; SC { Print e }
  | LBRACE; s = stmts; RBRACE { s }
  | SKIP; SC { Skip }
  ;

maybe_expr:
  | e = expr { Some e }
  | { None }
  ;

maybe_assign:
  | x = IDENT; EQ; e = expr { Some (Assign (x, e)) }
  | { None }
  ;

stmts:
  | { Skip }
  | s = stmt; ss = stmts { Cmp(s, ss) }
