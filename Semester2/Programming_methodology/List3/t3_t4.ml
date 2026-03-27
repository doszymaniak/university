type 'a tree =
| Leaf
| Node of 'a tree * 'a * 'a tree

let example_tree = Node (Node (Leaf, 2, Leaf), 5, Node (Node (Leaf, 7, Leaf), 9, Leaf))


(* Zadanie 3 *)
let rec fold_tree f acc t =
  match t with
  | Leaf -> acc
  | Node (l, n, r) -> f (fold_tree f acc l) n (fold_tree f acc r)

let tree_product t = fold_tree (fun l v r -> l * v * r) 1 t

let tree_flip t = fold_tree (fun l v r -> Node (r, v, l)) Leaf t

let tree_height t = fold_tree (fun l_h v r_h -> (max l_h r_h) + 1) 0 t

let tree_span t = fold_tree (
  fun l x r ->
    let left_min =
      match l with
      | None -> x
      | Some (v, _) -> v
    in
    let right_max =
      match r with
      | None -> x
      | Some (_, v) -> v
    in Some (left_min, right_max)
) None t

let flatten t = fold_tree (fun left v right -> left @ (v :: right)) [] t


(* Zadanie 4 *)
let rec flat_append t xs =
  match t with
  | Leaf -> xs
  | Node (left, v, right) -> 
      let with_right = flat_append right xs in
      flat_append left (v :: with_right)

let flatten_better t = flat_append t []