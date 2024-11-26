import Data.Text as T

concatStr :: String -> String -> Int
concatStr s1 s2 = (T.length (pack s1))  + (T.length (pack s2))

abbrev = "ikn"
fullname = "impcuong"

main = 
  print(concatStr abbrev fullname)
