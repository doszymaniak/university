(* Identity monad *)
module Id = struct
  type 'a t = 'a

  let return : 'a -> 'a t =
    fun v -> v

  let bind : 'a t -> ('a -> 'b t) -> 'b t =
    fun m f -> f m
end

(* Identity monad with a lazy computation type *)
module LazyId = struct
  type 'a t = unit -> 'a

  let return : 'a -> 'a t =
    fun v -> fun () -> v

  let bind : 'a t -> ('a -> 'b t) -> 'b t =
    fun m f ->
      fun () ->
        let v1 = m () in
        let v2 = f v1 in
        v2 ()
end