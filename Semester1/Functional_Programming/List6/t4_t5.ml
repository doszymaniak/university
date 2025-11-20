(* 
  The current continuation is the last argument of f
  The function f computes a new accumulator and passes it to fold_left_cps
  to continue processing the rest of the list
*)
let rec fold_left_cps :
  ('a -> 'b -> ('a -> 'c) -> 'c) -> 'a -> 'b list -> ('a -> 'c) -> 'c =
  fun f acc list k ->
    match list with
    | [] -> k acc
    | x :: xs -> f acc x (fun new_acc -> fold_left_cps f new_acc xs k)

(* 
  In this function, k is the continuation that represents processing 
  the rest of the list 
*)
let my_fold_left f acc list = 
  fold_left_cps (fun acc x k -> k (f acc x)) acc list (fun x -> x)

let for_all p xs =
  let k_end = (fun x -> x) in
  fold_left_cps (
    fun acc x k -> if p x then k acc
    else k_end false
  ) true xs k_end

let mult_list xs =
  let k_end = (fun x -> x) in
  fold_left_cps (
    fun acc x k -> if x = 0 then k_end 0
    else k (acc * x)
  ) 1 xs k_end

let sorted list =
  match list with 
  | [] | [_] -> true
  | x :: xs ->
      let not_sorted = min_int in
      let k_end = (fun x -> x) in
      let v = fold_left_cps (
        fun acc x k -> if x >= acc then k x 
        else k_end not_sorted
      ) x xs k_end in
      if v = not_sorted then false else true