module Main where

import Data.Char as C

inputPath = "1.input"

procLine :: String -> Int
procLine = read . firstLast . filter C.isDigit
  where firstLast xs = [head xs, last xs]

main = do
  input <- readFile inputPath
  putStrLn $ show $ sum $ map procLine $ lines input
