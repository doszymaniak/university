import StreamTrans

aux :: StreamTrans i o a -> [o] -> StreamTrans i b (a, [o])
aux (Return a) acc = Return (a, reverse acc)

aux (ReadS f) acc = ReadS (\mc ->
  case mc of
    Nothing -> aux (f Nothing) acc
    Just c -> aux (f (Just c)) acc
  )

aux (WriteS c f) acc = aux f (c : acc)

catchOutput :: StreamTrans i o a -> StreamTrans i b (a, [o])
catchOutput stream = aux stream []