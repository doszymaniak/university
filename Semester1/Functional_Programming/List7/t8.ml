type symbol = string

type 'v term =
| Var of 'v
| Sym of symbol * 'v term list

(* Inserting a variable into the tree *)
let return v = Var v

(* Substituting a variable *)
let rec bind t f =
  match t with
  | Var x -> f x
  | Sym (name, xs) -> Sym (name, List.map (fun x -> bind x f) xs)

let rec map_tree m f =
  match m with
  | Var x -> Var (f x)
  | Sym (name, xs) -> Sym (name, List.map (fun sub -> map_tree sub f) xs)

(* f(x, g(y)) *)
let term = Sym ("f", [Var "x"; Sym ("g", [Var "y"])])

let subst v =
  match v with
  | "x" -> Var "first var"
  | "y" -> Var "second var"
  | _ -> Var "another var"