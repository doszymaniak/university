module BT : sig
  type 'a t
  val return : 'a -> 'a t
  val bind : 'a t -> ('a -> 'b t) -> 'b t
  val fail : 'a t
  val flip : bool t
  val run : 'a t -> 'a Seq.t
end = struct
  type 'a t = 'a Seq.t

  let return x = List.to_seq [x]

  (* Concatenation of two sequences *)
  let bind m f = Seq.flat_map f m

  let fail = Seq.empty

  let flip = List.to_seq [true; false]

  let run m = m
end

type 'a regexp =
| Eps
| Lit of ('a -> bool)
| Or of 'a regexp * 'a regexp
| Cat of 'a regexp * 'a regexp
| Star of 'a regexp

let ( +% ) r1 r2 = Or (r1, r2)
let ( *% ) r1 r2 = Cat (r1, r2)

let rec match_regexp : 'a regexp -> 'a list -> 'a list option BT.t =
  fun reg word ->
    match reg with
    | Eps -> BT.return None

    | Lit p ->
        begin match word with
        | x :: xs when p x -> BT.return (Some xs)
        | _ -> BT.fail end
    
    | Or (reg1, reg2) ->
        BT.bind BT.flip (fun which ->
          if which = true then match_regexp reg1 word
          else match_regexp reg2 word
        )
    
    | Cat (reg1, reg2) ->
        (* Match the first part *)
        BT.bind (match_regexp reg1 word) (fun res ->
          match res with
          (* An empty match - we proceed on the same word *)
          | None -> match_regexp reg2 word
          (* Something got matched - we try to match the second part with the rest *)
          | Some xs -> match_regexp reg2 xs
        )
    
    | Star r ->
        BT.bind BT.flip (fun stop ->
          (* Match zero repetitions of r *)
          if stop = true then BT.return None
          (* Match one or more repetitions of r *)
          else
            (* Check the first match *)
            BT.bind (match_regexp r word) (fun res1 ->
              match res1 with
              (* Fail because there should be a match in this branch *)
              | None -> BT.fail
              | Some xs ->
                  (* Something got matched - we proceed on the rest *)
                  BT.bind (match_regexp (Star r) xs) (fun res2 ->
                    match res2 with
                    (* Nothing more to match *)
                    | None -> BT.return (Some xs)
                    (* Another repetition matched *)
                    | Some ys -> BT.return (Some ys)
                  )
            )
        )