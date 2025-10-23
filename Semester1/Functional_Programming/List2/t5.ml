(*
  Alternatywna implementacja funkcji merge z poprzedniego zadania
  Zamiast budowac wynikowa liste od przodu i odwracac wynik na koncu,
  odwracamy listy wejsciowe na poczatku i scalamy je od konca
  Dzieki temu elementy dodawane sa do akumulatora w poprawnej kolejnosci
  Porownania sa wykonywane odwrotnie (cmp y x zamiast cmp x y)
*)
let merge_no_rev cmp list1 list2 =
  let rec aux list1 list2 res =
    match list1, list2 with
    | [], [] -> res
    | x :: xs, [] -> aux xs list2 (x :: res)
    | [], x :: xs -> aux list1 xs (x :: res)
    | x :: xs, y :: ys ->
        if cmp y x then aux xs list2 (x :: res)
        else aux list1 ys (y :: res)
  in aux (List.rev list1) (List.rev list2) []

let halve list =
  let rec aux slow fast acc =
    match fast with
    | [] | [_] -> (List.rev acc, slow)
    | _ :: _ :: xs -> aux (List.tl slow) xs (List.hd slow :: acc)
  in aux list list []

let rec mergesort cmp list =
  match list with
  | [] | [_] -> list
  | _ ->
    let (left, right) = halve list in
    merge_no_rev cmp (mergesort cmp left) (mergesort cmp right)