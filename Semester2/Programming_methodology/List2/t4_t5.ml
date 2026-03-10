(* Task 4 *)
let mem x xs =
  let rec aux l =
    match l with
    | [] -> false
    | curr :: rest -> if curr = x then true else aux rest
  in aux xs

  
(* Task 5 *)
let maximum xs =
  match xs with
  | [] -> neg_infinity
  | x :: xs ->
    let rec aux l current_max =
      match l with
      | [] -> current_max
      | curr :: rest ->
          let current_max = if curr > current_max then curr else current_max in
          aux rest current_max
    in aux xs x