import StreamTrans
import System.IO
import Data.Char

toLowerS :: StreamTrans Char Char ()
toLowerS = ReadS (\mc ->
  case mc of
    Nothing -> Return ()
    Just c -> WriteS (toLower c) (toLowerS)
  )

runIOStreamTrans :: StreamTrans Char Char a -> IO a
runIOStreamTrans (Return a) = return a

runIOStreamTrans (ReadS f) = do
  eof <- isEOF
  if eof then runIOStreamTrans (f Nothing)
  else do
    c <- getChar
    runIOStreamTrans (f (Just c))

runIOStreamTrans (WriteS c f) = do
  putChar c
  runIOStreamTrans f