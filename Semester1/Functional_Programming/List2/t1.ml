(*
  Przechodzi liste od lewej do prawej
  f (f (f acc x1) x2) x3 
*)
let rec my_fold_left f acc list =
  match list with
  | [] -> acc
  | x :: xs -> my_fold_left f (f acc x) xs

(*
  Przechodzi liste od prawej do lewej
  f x1 (f x2 (f x3 acc))
*)
let rec my_fold_right f list acc =
  match list with
  | [] -> acc
  | x :: xs -> f x (my_fold_right f xs acc)

(* Dlugosc listy *)
let list_length list = List.fold_left (fun acc _ -> acc + 1) 0 list

(* Odwrocona lista *)
let rev list = List.fold_left (fun acc x -> x :: acc) [] list

(* Zastosowanie funkcji na kazdym elemencie *)
let map f list = List.fold_right (fun x acc -> (f x) :: acc) list []

(* Konkatenacja list *)
let append list1 list2 = List.fold_right (fun x acc -> x :: acc) list1 list2

(* Konkatenacja list z jednoczesnym odwroceniem pierwszej z nich *)
let rev_append list1 list2 = List.fold_left (fun acc x -> x :: acc) list2 list1

(* Wybiera tylko te elementy z listy, ktore spelniaja predykat *)
let filter p list = List.fold_right (fun x acc -> if p x then x :: acc else acc) list []

(* Zastosowanie funkcji na kazdym elemencie i odwrocenie listy *)
let rev_map f list = List.fold_left (fun acc x -> (f x) :: acc) [] list

let example_list = [1; 2; 3; 4]

let rec print_int_list list =
  match list with
  | [] -> print_newline ()
  | x :: xs -> print_int x; print_string " "; print_int_list xs

  
let () =
  print_string "TEST NA LISCIE: ";
  print_int_list example_list;
  print_newline ();

  print_string "Dlugosc listy: ";
  print_int (list_length example_list);
  print_newline ();

  print_string "Odwrocona lista: ";
  print_int_list (rev example_list);

  print_string "Lista z map zwiekszajacym kazdy element o 1: ";
  print_int_list (map (fun x -> x + 1) example_list);

  print_string "Dolaczenie do listy [5; 6]: ";
  print_int_list (append example_list [5; 6]);

  print_string "Odwrocenie listy i dolaczenie [5; 6]: ";
  print_int_list (rev_append example_list [5; 6]);

  print_string "Tylko parzyste: ";
  print_int_list (filter (fun x -> x mod 2 = 0) example_list);

  print_string "Odwrocona lista z map zwiekszajacym kazdy element o 1: ";
  print_int_list (rev_map (fun x -> x + 1) example_list);