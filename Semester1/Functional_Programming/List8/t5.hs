import StreamTrans

pipe :: StreamTrans i m a -> StreamTrans m o b -> StreamTrans i o b
pipe (Return a) stream2 =
  case stream2 of
    Return b -> Return b
    WriteS c f -> WriteS c (pipe (Return a) f)
    ReadS f -> pipe (Return a) (f Nothing)

pipe (WriteS c f) stream2 =
  case stream2 of
    Return a -> Return a
    WriteS d g -> WriteS d (pipe (WriteS c f) g)
    ReadS g -> pipe f (g (Just c))

pipe (ReadS f) stream2 = ReadS (\mc -> pipe (f mc) stream2)

(|>|) :: StreamTrans i m a -> StreamTrans m o b -> StreamTrans i o b
(|>|) stream1 stream2 = pipe stream1 stream2