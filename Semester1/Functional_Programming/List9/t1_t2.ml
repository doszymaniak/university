type empty = |

type _ fin_type =
| Unit : unit fin_type
| Bool : bool fin_type
| Pair : 'a fin_type * 'b fin_type -> ('a * 'b) fin_type
| Empty : empty fin_type
| LeftRight : 'a fin_type * 'b fin_type -> (('a, 'b) Either.t) fin_type

let rec all_values : type a. a fin_type -> a Seq.t =
  fun t ->
    match t with
    (* Sequence consisting of a single element *)
    | Unit -> Seq.return ()
    | Bool -> List.to_seq [true; false]
    | Pair (t1, t2) ->
        let seq1 = all_values t1 in
        let seq2 = all_values t2 in
        (* The Cartesian product of two sequences returns all possible combinations *)
        Seq.product seq1 seq2
    | Empty -> Seq.empty
    | LeftRight (t1, t2) ->
        (* All values of type t1 wrapped in Left *)
        let seq1 = Seq.map (fun x -> Either.left x) (all_values t1) in
        (* All values of type t2 wrapped in Right *)
        let seq2 = Seq.map (fun x -> Either.right x) (all_values t2) in
        Seq.append seq1 seq2