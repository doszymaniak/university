module type RandomMonad = sig
  type 'a t
  val return : 'a -> 'a t
  val bind : 'a t -> ('a -> 'b t) -> 'b t
  val random : int t
  val run : int -> 'a t -> 'a
end

module RS : sig include RandomMonad end = struct
  (* initial_seed -> (result, new_seed) *)
  type 'a t = int -> 'a * int

  let return v = fun seed -> (v, seed)

  let bind m f =
    fun seed -> 
      let (v1, new_seed) = m seed in
      (f v1) new_seed

  let random =
    fun seed ->
      let res = 16807 * (seed mod 127773) - 2836 * (seed / 127773) in
      if res > 0 then (res, res)
      else 
        let res = if res = 0 then 2147483646 else 2147483647 + res in
        (res, res)
  
  let run seed m = 
    let (x, new_seed) = m seed in x
end

module Shuffle (R : RandomMonad) : sig
  val shuffle : 'a list -> 'a list R.t
end = struct
  let rec get_value idx curr_idx list =
    match list with
    | x :: xs ->
        if curr_idx = idx then x
        else get_value idx (curr_idx + 1) xs
    | [] -> failwith "Index out of bounds!"

  let swap idx1 idx2 list =
    let v1 = get_value idx1 0 list in
    let v2 = get_value idx2 0 list in
    List.mapi (fun idx el ->
      if idx = idx1 then v2
      else if idx = idx2 then v1
      else el
    ) list

  let shuffle list =
    let n = List.length list in
    let rec outer curr_idx list =
      if curr_idx >= n then R.return list
      else
        R.bind R.random (fun r ->
          let idx_to_swap = r mod n in
          let new_list = swap curr_idx idx_to_swap list in
          outer (curr_idx + 1) new_list
        )
    in outer 0 list
end