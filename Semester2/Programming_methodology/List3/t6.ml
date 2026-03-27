module type DICT = sig
  type ('a, 'b) dict
  val empty : ('a, 'b) dict
  val insert : 'a -> 'b -> ('a, 'b) dict -> ('a, 'b) dict
  val remove : 'a -> ('a, 'b) dict -> ('a, 'b) dict
  val find_opt : 'a -> ('a, 'b) dict -> 'b option
  val find : 'a -> ('a, 'b) dict -> 'b
  val to_list : ('a, 'b) dict -> ('a * 'b) list
end

module ListDict : DICT = struct
  type ('a, 'b) dict = ('a * 'b) list

  let empty = []

  let rec remove a dict =
    List.filter (fun (el1, _) -> el1 <> a) dict

  let insert a b dict =
    let dict = remove a dict in
    let new_val = (a, b) in new_val :: dict

  let rec find_opt a dict =
    match dict with
    | [] -> None
    | (el1, el2) :: rest -> if el1 = a then Some el2 else find_opt a rest

  let rec find a dict =
    match dict with
    | [] -> failwith "Not found!"
    | (el1, el2) :: rest -> if el1 = a then el2 else find a rest

  let to_list dict = dict
end