let rec fix f x = f (fix f) x

let fib_f fib n =
  if n <= 1 then n
  else fib (n - 1) + fib (n - 2)

let fib = fix_memo fib_f

(* fib 3 = (fix fib_f) 3 = (fib_f (fix fib_f)) 3 = (fib_f fib) 3 *)

(*
  A fix function with an additional maximum recursion-depth parameter
  Throws an exception when the depth is exceeded
*)
let fix_with_limit : int -> (('a -> 'b) -> 'a -> 'b) -> 'a -> 'b = 
  fun max_dep f x ->
    let rec aux max_dep curr_dep f x =
      if curr_dep > max_dep then failwith "Recursion depth exceeded!"
      else f (aux max_dep (curr_dep + 1) f) x
    in aux max_dep 0 f x

(* A fix function with memoization *)
let fix_memo : (('a -> 'b) -> 'a -> 'b) -> 'a -> 'b =
  fun f x ->
    let table = Hashtbl.create 100 in 
    let rec aux f x =
      if Hashtbl.mem table x then Hashtbl.find table x 
      else 
        let v = f (aux f) x in Hashtbl.add table x v; v;
    in aux f x 