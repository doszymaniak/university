let split list =
  let n = List.length list in
  match list with
  | [] -> ([], [])
  | [x] -> ([x], [])
  | x :: xs ->
      let rec aux left list curr_n =
        match list with
        | [] -> failwith "won't happen"
        | x :: xs ->
            if curr_n = n / 2 then (left, list)
            else aux (x :: left) xs (curr_n + 1)
      in aux [] list 0

let merge xs ys =
  let rec aux left right acc =
    match left, right with
    | [], (x :: r) -> aux [] r (x :: acc)
    | (x :: l), [] -> aux l [] (x :: acc)
    | [], [] -> List.rev acc
    | (x :: xs), (y :: ys) ->
        if x < y then aux xs right (x :: acc)
        else aux left ys (y :: acc)
  in aux xs ys []

let rec merge_sort list =
  match list with
  | [] -> list
  | [x] -> list
  | x :: xs ->
      let left, right = split list in
      let sorted_left, sorted_right = merge_sort left, merge_sort right in
      merge sorted_left sorted_right