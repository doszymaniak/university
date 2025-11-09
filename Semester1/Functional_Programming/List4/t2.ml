type 'a zlist = 'a list * 'a option * 'a list 

let empty : 'a zlist = ([], None, [])

(* Converts a list into a zipper *)
let of_list : 'a list -> 'a zlist = 
  fun list ->
    match list with 
    | [] -> empty
    | x :: xs -> ([], Some x, xs)

(* Converts a zipper back into a list *)
let to_list : 'a zlist -> 'a list =
  fun (l, cur, r) ->
    match cur with
    | None -> List.rev_append l r
    | Some x -> List.rev_append l (x :: r)

(* Returns the first element after the cursor *)
let elem : 'a zlist -> 'a option =
  fun (_, _, r) ->
    match r with
    | [] -> None
    | x :: _ -> Some x

(* Moves the cursor one step to the left *)
let move_left : 'a zlist -> 'a zlist =
  fun (l, cur, r) ->
    match l with 
    | [] -> (l, cur, r) 
    | x :: xs ->
        match cur with 
        | None -> (xs, Some x, r)
        | Some c -> (xs, Some x, c :: r)

(* Moves the cursor one step to the right *)
let move_right : 'a zlist -> 'a zlist =
  fun (l, cur, r) ->
    match r with
    | [] -> (l, cur, r)
    | x :: xs -> 
        match cur with
        | None -> (l, Some x, xs)
        | Some v -> (v :: l, Some x, xs)

(* Inserts a new element and makes it the new cursor *)
let insert : 'a -> 'a zlist -> 'a zlist =
  fun x (l, cur, r) ->
    match cur with
    | None -> (l, Some x, r)
    | Some c -> (c :: l, Some x, r)

(* Removes the element to the left of the cursor *)
let remove : 'a zlist -> 'a zlist =
  fun (l, cur, r) ->
    match l with 
    | [] -> (l, cur, r) 
    | x :: xs -> (xs, cur, r)