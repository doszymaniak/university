type ('a, 'b) heap = Leaf | Node of ('a, 'b) heap * int * 'a * 'b * ('a, 'b) heap

let rank h =
  match h with
  | Leaf -> 0
  | Node (_, r, _, _, _) -> r

let mk_node (l, k, v, r) =
  let left_rank = rank l in
  let right_rank = rank r in
  if left_rank >= right_rank then Node (l, right_rank + 1, k, v, r)
  else Node (r, left_rank + 1, k, v, l)

let rec merge h1 h2 =
  match h1, h2 with
  | h1, Leaf -> h1
  | Leaf, h2 -> h2
  | Node (left1, _, k1, v1, right1), Node (left2, _, k2, v2, right2) ->
      if k1 <= k2 then
        let merged_part = merge right1 h2 in mk_node (left1, k1, v1, merged_part)
      else
        let merged_part = merge right2 h1 in mk_node (left2, k2, v2, merged_part)

type ('a, 'b) pq = ('a, 'b) heap

let empty = Leaf

let insert k v h = merge (Node (Leaf, 1, k, v, Leaf)) h

let pop h =
  match h with
  | Leaf -> failwith "empty heap!"
  | Node (l, _, _, _, r) -> merge l r

let min h =
  match h with
  | Leaf -> failwith "empty heap!"
  | Node (_, _, _, v, _) -> v

let min_prio h =
  match h with
  | Leaf -> failwith "empty heap!"
  | Node (_, _, k, _, _) -> k

(* 
  Funkcja pomocnicza do sortowania przez kopcowanie
  Zamienia liste na kopiec, klucz i wartosc sa takie same
*)
let rec to_heap xs res =
  match xs with
  | [] -> res
  | y :: ys -> to_heap ys (insert y y res)

(*
  Sortowanie przez kopcowanie:
  1) Zamieniamy liste na kopiec uzywajac funkcji "to_heap"
  2) Usuwamy element z najmniejszym kluczem i dodajemy do wyniku, powtarzamy dla calego kopca
  3) Na koncu odwracamy liste, aby odpowiedni porzadek pozostal zachowany
*)
let heapsort xs =
  let heap = to_heap xs Leaf in
  let rec aux h res =
    match h with
    | Leaf -> List.rev res
    | _ -> aux (pop h) ((min h) :: res)
  in aux heap []