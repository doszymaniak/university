let rec scan f acc s n =
  if n = 0 then f acc (s 0)
  else f (scan f acc s (n - 1)) (s n)

let nat = fun n -> n
let square = fun n -> n * n
let test_n = 10

let print_int_stream s n =
  for i = 0 to n - 1 do
      print_int (s i);
      print_string " "
  done;
  print_newline ()

let test s =
  print_int_stream s test_n;
  print_string "SCAN Z FUNKCJA (+): ";
  print_int_stream (scan (+) 0 s) test_n

let () =
  print_endline "TEST DLA LICZB NATURALNYCH";
  test nat;
  print_newline ();

  print_endline "TEST DLA KWADRATOW";
  test square