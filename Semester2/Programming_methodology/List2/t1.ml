let rec fib_rec n =
  if n = 0 then 0
  else if n = 1 then 1
  else fib_rec (n - 1) + fib_rec (n - 2)

let fib_iter n =
  if n = 0 then 0
  else if n = 1 then 1
  else if n = 2 then 1
  else
    let rec aux first second i =
      if i = n then first + second
      else aux second (first + second) (i + 1)
    in aux 1 1 3

(*
  Recursive: O(2^n)
  Iterative: O(n)
*)