(*
  Przechodze liste od prawej do lewej
  Dodaje x do pierwszego sufiksu z akumulatora i dolaczam wynik do reszty sufiksow
*)
let suffixes list =
  List.fold_right (fun x acc -> (x :: List.hd acc) :: acc) list [[]]

let rec last_element list =
  match list with
  | [] -> failwith "empty list"
  | [x] -> x
  | x :: xs -> last_element xs

(*
  Przechodze liste od lewej do prawej
  Dodaje x do ostatniego prefiksu z akumulatora i dolaczam wynik do reszty prefiksow
*)
let prefixes list =
  List.fold_left (fun acc x -> acc @ [last_element acc @ [x]]) [[]] list