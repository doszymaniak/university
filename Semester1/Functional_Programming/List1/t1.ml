(* fun x -> x ma typ 'a -> 'a *)
(* Funkcja identycznosciowa majaca typ int -> int to fun (x : int) -> x *)

(* 
  Wyrazenie typu ('a -> 'b) -> ('c -> 'a) -> 'c -> 'b 
  f : 'a -> 'b
  g : 'c -> 'a
  x : 'c 

  Skladamy:
  1) g x : 'a
  2) f (g x) : 'b <----- czyli to co chcemy
*)
let fun1 f g x = f (g x)

(* 
  Wyrazenie typu 'a -> 'b -> 'a
  Funkcja przyjmujaca dwa argumenty dowolnych typow, zwraca wartosc pierwszego typu
*)
let fun2 a b = a

(*
  Wyrazenie typu 'a -> 'a -> 'a
  Podobnie jak poprzednio, tylko musimy wymusic taki sam typ dla obu argumentow
*)
let fun3 (a : 'a) (b : 'a) = a