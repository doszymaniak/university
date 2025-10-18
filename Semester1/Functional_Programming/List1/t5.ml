let nat = fun n -> n
let square = fun n -> n * n
let idx1 = 3
let idx2 = 8

let tabulate ?(idx1=0) idx2 s =
  let rec aux x list =
    if x = idx1 then s x :: list
    else aux (x - 1) ((s x) :: list)
  in aux idx2 []

let rec print_int_list list =
  match list with
  | [] -> print_string ""
  | [x] -> print_int x; print_string " "
  | x :: xs -> print_int x; print_string " "; print_int_list xs

let () =
  print_string "LICZBY NATURALNE Z ZAKRESU OD IDX1 DO IDX2: ";
  let list = tabulate ~idx1 idx2 nat in
  print_int_list list;

  print_newline ();
  print_string "KWADRATY Z ZAKRESU OD IDX1 DO IDX2: ";
  let list = tabulate ~idx1 idx2 square in
  print_int_list list;
  print_newline()