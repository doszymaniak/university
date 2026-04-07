(* Task 2 *)
let matrix_mult m n =
  let a, b, c, d = m in
  let e, f, g, h = n in
  (a * e + b * g, a * f + b * h, c * e + d * g, c * f + d * h)

let matrix_id = (1, 0, 0, 1)

let matrix_expt m k =
  let rec aux i res =
    if i = k then res
    else aux (i + 1) (matrix_mult res m)
  in 
  if k = 0 then matrix_id
  else aux 1 m

let fib_matrix k =
  let m = (1, 1, 1, 0) in
  let multiplied = matrix_expt m k in
  let _, res, _, _ = multiplied in
  res


(* Task 3 *)
let rec matrix_expt_fast m k =
  if k = 0 then matrix_id
  else
    let t = matrix_expt_fast m (k / 2) in
    if k mod 2 = 0 then matrix_mult t t
    else matrix_mult m (matrix_mult t t)

let fib_fast k =
  let m = (1, 1, 1, 0) in
  let multiplied = matrix_expt_fast m k in
  let _, res, _, _ = multiplied in
  res