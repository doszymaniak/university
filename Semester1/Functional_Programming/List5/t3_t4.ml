type 'a lazy_tree = 'a node lazy_t
and 'a node = Node of 'a lazy_tree * ('a * 'a) * 'a lazy_tree

(*
  Creates an infinite lazy tree of rational numbers
  Each node is constructed by taking the mediant (a + c) / (b + d)
  between the fractions a / b and c / d
*)
let rational_num_tree = 
  let l_range = (0, 1) in 
  let r_range = (1, 0) in 
  let rec aux left right = 
    let v1 = fst left + fst right in 
    let v2 = snd left + snd right in 
    let v = (v1, v2) in 
    lazy (Node (aux left v, v, aux v right))
  in aux l_range r_range

(* 
  Creates a stream of rational numbers 
  Iterates through the rational_num_tree in the following order:
  root -> root's children -> children of root's children -> ...
*)
let rational_num_stream = 
  let rec aux tree () =
    let Node (left, root, right) = Lazy.force tree in
    let rest = Seq.interleave (aux left) (aux right) in 
    Seq.Cons (root, rest)
  in aux rational_num_tree