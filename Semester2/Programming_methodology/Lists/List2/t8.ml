let select list =
  let rec find_minimum list curr_min =
    match list with
    | [] -> curr_min
    | x :: xs -> 
        if x < curr_min then find_minimum xs x
        else find_minimum xs curr_min
  in
  match list with
  | [] -> failwith "empty list!"
  | x :: xs ->
      let minimum_el = find_minimum xs x in
      let rec make acc l =
        match l with
        | [] -> failwith "won't happen"
        | y :: ys when y = minimum_el ->
            (minimum_el, (List.rev acc) @ ys)
        | y :: ys -> make (y :: acc) ys
      in make [] list

let select_sort list =
  match list with
  | [] -> []
  | x :: xs ->
      let rec aux l acc =
        match l with
        | [] -> List.rev acc
        | _ ->
            let (min_el, rest) = select l in
            aux rest (min_el :: acc)
      in aux list []