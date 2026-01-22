type 'a dllist = 'a dllist_data lazy_t
and 'a dllist_data =
{
  prev : 'a dllist;
  elem : 'a;
  next : 'a dllist
}

let rec make_prev next next_val =
  let rec node = lazy {prev = make_prev node (next_val - 1); elem = next_val - 1; next = next} in node

let rec make_next prev prev_val =
  let rec node = lazy {prev = prev; elem = prev_val + 1; next = make_next node (prev_val + 1)} in node

let integers : int dllist =
  let rec node = lazy {prev = make_prev node 0; elem = 0; next = make_next node 0} in node