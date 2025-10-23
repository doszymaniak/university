(*
  Przechodze liste od prawej do lewej, zaczynam z acc = [[]]
  Doklejam x na poczatku kazdej podlisty z acc
  Wynik lacze z aktualnymi podlistami z acc
*)
let sublists list =
  List.fold_right (fun x acc -> acc @ (List.map (fun sub -> x :: sub) acc)) list [[]]
