(*
  Zamkniete wyrazenia typu 'a -> 'a -> 'a maja tylko dwie mozliwe wartosci
  Sa to funkcje przyjmujace dwa argumenty tego samego typu i zwracajace wartosc
  tego samego typu
  Typ 'a jest zbyt ogolny, wiec nie mozemy wykonywac na nim zadnych operacji
  Jedyna mozliwoscia jest zwrocenie jednego z dwoch argumentow
*)

let ctrue : 'a -> 'a -> 'a = fun x y -> x
let cfalse : 'a -> 'a -> 'a = fun x y -> y

(* 
  Jesli x jest ctrue, wtedy wynik zalezy od y
  Wpp od razu zwracamy drugi argument, czyli b
*)
let cand : ('a -> 'a -> 'a) -> ('a -> 'a -> 'a) -> ('a -> 'a -> 'a) =
  fun x y a b -> x (y a b) b

(*
  Jesli x jest ctrue, wtedy od razu zwracamy pierwszy argument, czyli a
  Wpp wynik zalezy od y
*)
let cor : ('a -> 'a -> 'a) -> ('a -> 'a -> 'a) -> ('a -> 'a -> 'a) =
  fun x y a b -> x a (y a b)

let cbool_of_bool : bool -> 'a -> 'a -> 'a =
  fun x -> if x = true then ctrue else cfalse 

(*
  Jesli x jest ctrue, wtedy zwracamy pierwszy argument, czyli true
  Wpp zwracamy false
*)
let bool_of_cbool : (bool -> bool -> bool) -> bool =
  fun x -> x true false

(*
  Typy niektorych z tych funkcji moga roznic sie od typow znalezionych przez 
  algorytm rekonstrukcji typow, poniewaz algorytm uogolnia je jak 
  najbardziej, to znaczy na przyklad zamiast'a -> 'a -> 'a 
  moze podac 'a -> 'b -> 'c
*)