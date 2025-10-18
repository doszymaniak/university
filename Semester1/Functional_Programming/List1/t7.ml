let zero : ('a -> 'a) -> 'a -> 'a =
  fun f x -> x

let one : ('a -> 'a) -> 'a -> 'a =
  fun f x -> f x

let two : ('a -> 'a) -> 'a -> 'a = 
  fun f x -> f (f x)

let three : ('a -> 'a) -> 'a -> 'a =
  fun f x -> f (f (f x))

(* Zeby otrzymac kolejna liczbe naturalna, musimy zaaplikowac jeszcze raz f do aktualnej *)
let succ : (('a -> 'a) -> 'a -> 'a) -> ('a -> 'a) -> 'a -> 'a =
  fun n f x -> f (n f x)

(* Zeby dodac dwie liczby naturalne, musimy uzyc funkcji f (n + k) razy *)
let add : (('a -> 'a) -> 'a -> 'a) -> (('a -> 'a) -> 'a -> 'a) -> ('a -> 'a) -> 'a -> 'a =
  fun n k f x -> k f (n f x)

(* Zeby pomnozyc dwie liczby naturalne, musimy uzyc funkcji f (n * k) razy *)
(*
  Przyklad mnozenia dwoch funkcji:
  Niech k f = three f
  Wtedy three f = x -> f (f (f x))
  Czyli to po prostu funkcja f zaaplikowana 3 razy
*)
let mul : (('a -> 'a) -> 'a -> 'a) -> (('a -> 'a) -> 'a -> 'a) -> ('a -> 'a) -> 'a -> 'a =
  fun n k f x -> n (k f) x

let ctrue : 'a -> 'a -> 'a = fun x y -> x
let cfalse : 'a -> 'a -> 'a = fun x y -> y
(* 
  Jesli n jest zerem, to od razu zwroci ctrue
  Wpp funkcja _ -> cfalse zostanie zaaplikowana przynajmniej raz
*)
let is_zero : (('a -> 'a) -> 'a -> 'a) -> 'a -> 'a -> 'a = 
  fun n ctrue cfalse -> n (fun _ -> cfalse) ctrue

let cnum_of_int : int -> ('a -> 'a) -> 'a -> 'a =
  fun n ->
    let rec aux curr curr_cnum =
      if curr = n then curr_cnum
      else aux (curr + 1) (succ curr_cnum)
    in aux 0 zero

let rec cnum_of_int_2 x =
  if x = 0 then zero
  else succ (cnum_of_int (x - 1))

let int_of_cnum : ((int -> int) -> int -> int) -> int =
  fun n -> n (fun x -> x + 1) 0