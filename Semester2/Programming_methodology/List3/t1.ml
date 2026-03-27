let square n = n * n

let inc n = n + 1

let compose f g n = f (g n)

(*
  compose square inc 5 = square (inc 5) = square 6 = 36

  compose inc square 5 = inc (square 5) = inc 25 = 26
*)