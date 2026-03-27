(* 
  [1; 2; 3; 4]
  f 1 (f 2 (f 3 (f 4 acc)))
*)
let rec my_fold_right f xs acc =
  match xs with
  | [] -> acc
  | x :: xs -> f x (my_fold_right f xs acc)

(*
  [1; 2; 3; 4]
  1) f 1 ...
  2) f 2 ...
  3) f 3 ...
  4) f 4 ...
  5) []
  6) f 4 [] = [4]
  7) f 3 [4] = [4; 3]
  8) f 2 [4; 3] = [4; 3; 2]
  9) f 1 [4; 3; 2] = [4; 3; 2; 1]
*)
let fold_right_rev xs = List.fold_right (fun y ys -> ys @ [y]) xs []

(*
  Wada tej implementacji jest zlozonosc czasowa
  Dla kazdego y, ys funkcja wykonuje k - 1 List.consow (gdzie k to dlugosc ys)
  Czyli 0, 1, 2, 3, ..., n - 1 = n * (n - 1) / 2
  Dodatkowo w kazdym kroku tworzymy liste z jednego elementu [y]
  Wiec razem mamy n * (n - 1) / 2 + n = n * (n + 1) / 2 consow
  Wszystkie posrednio tworzone listy to nieuzytki, bo interesuje nas tylko lista wynikowa,
  zatem jest ich n * (n - 1) / 2
*)

(* Jak dziala @: *)
let rec append list1 list2 =
  match list1 with
  | [] -> list2
  | x :: xs -> x :: (append xs list2)

(* Alternatywna implementacja *)
let fold_left_rev xs = List.fold_left (fun acc x -> x :: acc) [] xs