(*
  Implementacja drzew lewicowych:
  - w kazdym wezle przechowywana wartosc jest <= wartosci w jego dzieciach,
  - dla kazdego wezla dlugosc prawego kregoslupa lewego dziecka jest >= dlugosc
    prawego kregoslupa prawego dziecka
  
  W wierzcholku przechowywana jest etykieta, dlugosc prawego kregoslupa 
  oraz dzieci (poddrzewa)
*)
type 'a leftist_tree =
| Leaf
| Node of 'a * int * 'a leftist_tree * 'a leftist_tree

(* 
  Tworzenie wezla z dwoch drzew i etykiety
  Zakladamy, ze etykieta jest <= wszystkie etykiety w wezlach danych drzew
*)
let smart_constructor x tree1 tree2 =
  let left_len =
    match tree1 with
    | Leaf -> 0
    | Node (_, len, _, _) -> len
  in
  let right_len = 
    match tree2 with
    | Leaf -> 0
    | Node (_, len, _, _) -> len
  in 
  if left_len >= right_len then Node (x, right_len + 1, tree1, tree2)
  else Node (x, left_len + 1, tree2, tree1)

(* Scalanie dwoch drzew w jedno *)
let rec merge tree1 tree2 =
  match tree1, tree2 with
  | Leaf, t | t, Leaf -> t
  | Node (x1, _, left1, right1), Node (x2, _, left2, right2) ->
      if x1 <= x2 then
        let merged = merge right1 tree2 in
        smart_constructor x1 left1 merged
      else 
        let merged = merge right2 tree1 in
        smart_constructor x2 left2 merged

(* Wstawianie nowego elementu *)
let insert x tree =
  merge tree (Node (x, 1, Leaf, Leaf))

(* Usuwanie najmniejszego elementu, czyli korzenia *)
let remove_smallest tree =
  match tree with
  | Leaf -> Leaf
  | Node (x, _, left, right) -> merge left right