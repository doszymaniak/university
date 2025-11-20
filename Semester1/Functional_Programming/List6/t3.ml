exception Stop

let for_all : ('a -> bool) -> 'a list -> bool =
  fun p list ->
    try
      List.fold_left (fun _ x -> if p x then true else raise Stop) true list
    with 
      Stop -> false

let mult_list : int list -> int =
  fun list ->
    try
      List.fold_left (fun acc x -> if x = 0 then raise Stop else acc * x) 1 list
    with
      Stop -> 0

let sorted : int list -> bool =
  fun list ->
    try
      match list with
      | [_] | [] -> true
      | x :: xs ->
          let _ = List.fold_left (fun acc y -> if y < acc then raise Stop else y) x xs in
          true
    with
      Stop -> false