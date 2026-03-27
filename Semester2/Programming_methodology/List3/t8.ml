module Freq (D : DICT) = struct
  let freq (xs : 'a list) : ('a * int) list =
    let dict = List.fold_left (
      fun res x ->
        match D.find_opt x res with
        | None -> D.insert x 1 res
        | Some c -> D.insert x (c + 1) res
    ) D.empty xs in
    List.rev (D.to_list dict)
end

module F = Freq(ListDict)

let list_of_string s = String.to_seq s |> List.of_seq

let char_freq s = F.freq (list_of_string s)