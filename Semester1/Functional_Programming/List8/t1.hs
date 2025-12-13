import Data.Char
import System.IO

echoLower :: IO ()
echoLower = do
  eof <- isEOF
  if eof then return ()
  else do
    c <- getChar
    putChar (toLower c)
    echoLower