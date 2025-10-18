(*
  Funkcja typu 'a -> 'b
  Dla dowolnego wejscia typu 'a zwraca dowolne wyjscie typu 'b
  Taka funkcja nie moze zrobic nic z pierwszym argumentem (oprocz np. wypisania),
  poniewaz nie zna jego typu
  Moze zwrocic stala wartosc, ale wtedy typ wyjscia bedzie juz okreslony
  Jedyna mozliwoscia jest funkcja rzucajaca wyjatek lub nieskonczona rekurencja
*)

let fun1 x = failwith "cannot convert 'a to 'b"
let rec fun2 x = fun2 x