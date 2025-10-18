(* Glowa - pierwszy element strumienia *)
let hd s = s 0

(* Ogon - strumien bez glowy, czyli przesuniety o 1 *)
let tl s = fun n -> s (n + 1)

(* Strumien, ktorego kazdy element jest powiekszony o wartosc a *)
let add a s = fun n -> (s n) + a

(* Strumien z zaaplikowana funkcja f do kazdego elementu *)
let map f s = fun n -> f (s n)

(* Strumien z zaaplikowana funkcja dwuargumentowa f do dwoch elementow z dwoch strumieni *)
let map2 f s k = fun n -> f (s n) (k n)

(* Strumien z takimi samymi wartosciami oprocz elementu k-tego ktory ma wartosc a *)
let replace k a s = fun n -> if n = k then a else s n

(* Strumien zlozony z co k-tego elementu danego strumienia *)
let take_every k s = fun n -> s (n * k)

let print_int_stream s n =
  for i = 0 to n - 1 do
      print_int (s i);
      print_string " "
  done;
  print_newline ()

let test s test_n =
  print_string "GLOWA: ";
  print_endline (string_of_int (hd s));

  print_string "OGON: ";
  print_int_stream (tl s) test_n;

  print_string "POWIEKSZONY O 1: ";
  print_int_stream (add 1 s) test_n;

  let add_five x = x + 5 in
  print_string "APLIKACJA FUNKCJI ADD_FIVE: ";
  print_int_stream (map add_five s) test_n;

  print_string "PODMIANA INDEKSU NR 3 NA 1000: ";
  print_int_stream (replace 3 1000 s) test_n;

  print_string "STRUMIEN ZLOZONY Z CO DRUGIEGO ELEMENTU: ";
  print_int_stream (take_every 2 s) test_n;;

let nat = fun n -> n
let square = fun n -> n * n
let test_n = 10


let () =
  print_endline "TEST STRUMIENIA LICZB NATURALNYCH";
  print_int_stream nat test_n;
  test nat test_n;

  print_newline ();
  print_endline "TEST STRUMIENIA KWADRATOW";
  print_int_stream square test_n;
  test square test_n;

  print_newline();
  print_string "APLIKACJA DWUARGUMENTOWEJ FUNKCJI (+) DO NAT I SQUARE: ";
  print_int_stream (map2 (+) nat square) test_n