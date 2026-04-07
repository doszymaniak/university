module type DICT = sig
  type ('a, 'b) dict
  val empty : ('a, 'b) dict
  val insert : 'a -> 'b -> ('a, 'b) dict -> ('a, 'b) dict
  val remove : 'a -> ('a, 'b) dict -> ('a, 'b) dict
  val find_opt : 'a -> ('a, 'b) dict -> 'b option
  val find : 'a -> ('a, 'b) dict -> 'b
  val to_list : ('a, 'b) dict -> ('a * 'b) list
end

module TreeDict : DICT = struct
  type ('a, 'b) dict = Leaf | Node of ('a, 'b) dict * 'a * 'b * ('a, 'b) dict

  let empty = Leaf

  let rec insert a b dict =
    match dict with
    | Leaf -> Node (Leaf, a, b, Leaf)
    | Node (left, el1, el2, right) ->
        if el1 = a then Node (left, a, b, right)
        else if a < el1 then Node (insert a b left, el1, el2, right)
        else Node (left, el1, el2, insert a b right)

  let rec find_min dict =
    match dict with
    | Leaf -> None
    | Node (Leaf, a, b, _) -> Some (a, b)
    | Node (left, _, _, _) -> find_min left

  let rec remove a dict =
    match dict with
    | Leaf -> dict
    | Node (left, el1, el2, right) ->
        if a < el1 then Node (remove a left, el1, el2, right)
        else if a > el1 then Node (left, el1, el2, remove a right)
        else
          match left, right with
          | Leaf, _ -> right
          | _, Leaf -> left
          | _ -> 
              let x = find_min right in
              (match x with
              | None -> left
              | Some (new_a, new_b) -> Node (left, new_a, new_b, remove new_a right))

  let rec find_opt key dict =
    match dict with
    | Leaf -> None
    | Node (left, a, b, right) ->
        if a = key then Some b
        else if a < key then find_opt key right
        else find_opt key left

  let rec find key dict =
    match dict with
    | Leaf -> failwith "not found!"
    | Node (left, a, b, right) ->
        if a = key then b
        else if a < key then find key right
        else find key left

  let rec flat_append t xs =
    match t with
    | Leaf -> xs
    | Node (left, a, b, right) -> 
        let with_right = flat_append right xs in
        flat_append left ((a, b) :: with_right)

  let rec to_list dict = flat_append dict []
end