{-# LANGUAGE TypeApplications #-}

-- ghc-9.4.8 -O test.hs

import Data.Text (Text)
import qualified Data.Text as T
import Data.Typeable (Typeable, typeOf)

charToText :: Char -> Text
charToText c = T.singleton c

-- Alternative using fromString (less efficient for single characters):
charToTextFromString :: Char -> Text
charToTextFromString c = T.pack [c]

printType :: (Typeable a) => a -> IO ()
printType x = print (typeOf x)

printAsscType :: (Typeable a, Show a) => a -> String
printAsscType v = show v ++ " ~ " ++ show (typeOf v)

main :: IO ()
main = do
  print (charToText 'A')           -- Output: "A"
  print (charToText 'λ')           -- Output: "λ"
  print (charToTextFromString 'B') -- Output: "B"

  let sth = 'A'
  -- print $ sth <$ print (typeOf sth)
  putStrLn (printAsscType sth)

  let str = T.pack "dude_pls_stop"
  putStrLn (printAsscType str)

  printType (5 :: Int)
  putStrLn (printAsscType (100 :: Int))
  printType ("dude" :: String)
