import StreamTrans

listTrans :: StreamTrans i o a -> [i] -> ([o], a)
listTrans (Return a) input = ([], a)

listTrans (ReadS f) input =
  case input of
    [] -> listTrans (f Nothing) []
    x : xs -> listTrans (f (Just x)) xs

listTrans (WriteS c f) input = 
  let (out, val) = listTrans f input in (c : out, val)

runCycle :: StreamTrans a a b -> b
runCycle stream = val where (out, val) = listTrans stream out