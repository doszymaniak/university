(* 
  Funkcja rekurencyjna scalajaca dwie listy w zadanym porzadku 
  Zakladamy, ze listy na wejsciu sa juz uporzadkowane
*)
let rec merge_rec cmp list1 list2 =
  match list1, list2 with
  | [], list | list, [] -> list
  | x :: xs, y :: ys ->
      if cmp x y then x :: (merge_rec cmp xs list2)
      else y :: (merge_rec cmp list1 ys)

(* Scalanie z rekurencja ogonowa *)
let merge cmp list1 list2 =
  let rec aux list1 list2 res =
    match list1, list2 with
    | [], [] -> List.rev res
    | x :: xs, [] -> aux xs list2 (x :: res)
    | [], x :: xs -> aux list1 xs (x :: res)
    | x :: xs, y :: ys ->
        if cmp x y then aux xs list2 (x :: res)
        else aux list1 ys (y :: res)
  in aux list1 list2 []

(* 
  Obie wersje merge spelniaja swoje funkcje przy malych listach
  Jednak wersja bez rekurencji ogonowej powoduje przepelnienie stosu przy duzych listach
*)
let big1 = List.init 1000000 (fun x -> x + 1) 
let big2 = List.init 1000000 (fun x -> 2 * x) 

(*
  Dzieli liste na dwie polowy metoda dwoch wskaznikow
  Slow przesuwa sie o jeden element na raz, fast o dwa
  W kazdym kroku dodajemy do akumulatora to, co zebral slow
  Gdy fast dotrze do konca, w akumulatorze mamy lewa polowe,
  a w slow to, co pozostalo
*)
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
    merge cmp (mergesort cmp left) (mergesort cmp right)