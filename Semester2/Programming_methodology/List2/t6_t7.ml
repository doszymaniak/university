(* Task 6 *)
let suffixes xs =
  let rec aux l acc =
    match l with
    | [] -> List.rev ([] :: acc)
    | x :: xs -> aux xs (l :: acc)
  in aux xs []


(* Task 7 *)
let is_sorted xs =
  let rec aux l =
    match l with
    | [] -> true
    | [x] -> true
    | x :: y :: ys ->
        if x <= y then aux (y :: ys)
        else false
  in aux xs