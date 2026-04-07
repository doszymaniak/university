type ('a, 'b) heap = Leaf | Node of ('a, 'b) heap * int * 'a * 'b * ('a, 'b) heap

val mk_node : ('a, 'b) heap * 'a * 'b * ('a, 'b) heap -> ('a, 'b) heap
val merge : ('a, 'b) heap -> ('a, 'b) heap -> ('a, 'b) heap

type ('a, 'b) pq = ('a, 'b) heap

val empty : ('a, 'b) pq
val insert : 'a -> 'b -> ('a, 'b) pq -> ('a, 'b) pq
val pop : ('a, 'b) pq -> ('a, 'b) pq
val min : ('a, 'b) pq -> 'b
val min_prio : ('a, 'b) pq -> 'a

val heapsort : 'a list -> 'a list