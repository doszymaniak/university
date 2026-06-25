type column = string

type row = Eval.value list

type table = column list * row list

type query =
(* 
  Uwaga - aby zachowac sygnature musialam zrobic sekwencje zapytan w tym samym typie,
  wiec dostosowalam tez regule w parserze (przypadek bazowy).
  Regula w parserze dla query wyglada tak:

  query:
  | q = atomic_query; SC; EOF { q }
  | q = atomic_query; SC; qs = query { Seq (q, qs) }

  Reszte pozostawilam bez zmian (tylko uzupelnilam skladnie abstrakcyjna)
*)
| Seq of query * query
| Filter of Ast.expr
| Drop of column
| AddCol of column * Ast.expr
| Limit of int 
| Row_num of column 

(* 
  Funkcja pomocnicza tworzaca srodowisko dla danego wiersza
  Pod kazda nazwe kolumny podstawiamy odpowiadajaca wartosc z wiersza do srodowiska
*)
let rec make_row_env names row env =
  match names, row with
  | [], [] -> env
  | curr_name :: xs, curr_val :: ys -> make_row_env xs ys (Eval.Env.add curr_name curr_val env)
  | _ -> failwith "lenghts don't match!"

let rec eval (q : query) (t : table) : table =
  let (names, rows) = t in
  match q with
  (* Najpierw ewaluujemy jedno wyrazenie, wynikowa tabele przekazujemy do kolejnego *)
  | Seq (q1, q2) -> let t1 = eval q1 t in eval q2 t1

  (* 
    Dla kazdego wiersza obliczamy wartosc wyrazenia w srodowisku tego wiersza
    Pozostawiamy te ktore obliczaja sie do prawdy
  *)
  | Filter e ->
      let new_rows =
        List.filter (
          fun curr_row ->
            let row_env = make_row_env names curr_row (Eval.Env.empty) in
            let v = Eval.eval row_env e in
            match v with
            | VBool true -> true
            | _ -> false
        ) rows
      in (names, new_rows)

  (* 
    W nazwach kolumn szukam indeksu o odpowiadajacej nazwie
    Nastepnie mapuje funkcje pomocnicza na kazdym wierszu
    Funkcja pomocnicza przechodzi przez caly wiersz i gdy trafimy na element o znalezionym
    indeksie, to nie dodajemy go do zwracanej listy (nowego wiersza)
  *)
  | Drop col ->
      let col_idx = List.find_index (fun name -> name = col) names in
      begin match col_idx with
      | None -> failwith "no index found!"
      | Some idx ->
          let rec remove_el curr_idx res row =
            (match row with
            | x :: xs -> 
                if curr_idx = idx then remove_el (curr_idx + 1) res xs
                else remove_el (curr_idx + 1) (x :: res) xs
            | [] -> List.rev res)
          in
          let new_names = remove_el 0 [] names in
          let new_rows = List.map (fun row -> remove_el 0 [] row) rows in
          (new_names, new_rows) end
  
  (*
    Przechodze po wszystkich wierszach, obliczam wartosc wyrazenia w srodowisku
    danego wiersza a nastepnie doklejam wartosc na sam poczatek
    Do nazw kolumn rowniez doklejam nazwe kolumny na poczatek
    Nowa kolumna jest jako pierwsza poniewaz kolejnosc kolumn nie ma znaczenia
    a dodawanie na poczatek zamiast na koniec jest mniej kosztowne (O(1) vs O(n))
  *)
  | AddCol (col, e) ->
      let new_rows = 
        List.map (
          fun curr_row ->
            let row_env = make_row_env names curr_row (Eval.Env.empty) in
            let new_val = Eval.eval row_env e in
            new_val :: curr_row
        ) rows
      in let new_names = col :: names
      in (new_names, new_rows)

  (*
    Przechodze po wszystkich wierszach, jesli licznik wierszy przekroczyl juz
    n lub doszlismy do konca to zwracamy wynik
  *)
  | Limit n ->
      let rec limit_rows curr_cnt rows res =
        begin match rows with
        | curr_row :: rest -> 
            if curr_cnt <= n then limit_rows (curr_cnt + 1) rest (curr_row :: res)
            else List.rev res
        | [] -> List.rev res end
      in (names, limit_rows 1 rows [])


  (*
    Przechodze po wszystkich wierszach
    Dla aktualnego wiersza doklejam na poczatek wartosc z aktualnym licznikiem
  *)
  | Row_num col ->
      let new_names = col :: names in
      let rec add_cnt_el curr_cnt rows res =
        begin match rows with
        | curr_row :: rest -> add_cnt_el (curr_cnt + 1) rest (((Eval.VInt curr_cnt) :: curr_row) :: res)
        | [] -> List.rev res end
      in let new_rows = add_cnt_el 0 rows [] in
      (new_names, new_rows)