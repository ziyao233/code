module Main where

import qualified Data.Char as C
import qualified Data.List as L
import qualified Data.Tuple
import Data.Maybe
import Debug.Trace

inputPath = "3.input"

isSymbol :: Char -> Bool
isSymbol c = (not $ C.isDigit c) && (c /= '.')

symbolInLine :: String -> [Int]
symbolInLine = snd . foldl f (0, [])
  where f (n, xs) c = (n + 1, if isSymbol c then n : xs else xs)

-- (Number, (line, index, length))
numberInLine :: Int -> String -> [(Int, (Int, Int, Int))]
numberInLine _ "" = []
numberInLine l xs@(x:xs')
 | C.isDigit x = (read n, (l, length xs', length n)) : (numberInLine l xs'')
 | otherwise   = numberInLine l xs'
 where (n, xs'') = span C.isDigit xs

numbers xss =
  concat $ map (uncurry numberInLine) $ zip [0 .. (length xss - 1)] xss

index :: Int -> [a] -> Maybe a
index i xs
  | i < 0    = Nothing
  | otherwise = foldr (\x r k -> case k of
                                   0 -> Just x
                                   _ -> r (k - 1)) (const Nothing) xs i
indexr :: Int -> [a] -> Maybe a
indexr i xs = index ((length xs) - i - 1) xs

surrounds :: [String] -> (Int, Int, Int) -> String
surrounds xss (y, x, l) =
  catMaybes [ts >>= indexr (x + 1), ts >>= indexr (x - l)] ++ uc ++ dc
  where us = index (y - 1) xss
        ts = index y xss
        ds = index (y + 1) xss
        uc = mapMaybe (us >>=) $ map indexr [(x - l) .. (x + 1)]
        dc = mapMaybe (ds >>=) $ map indexr [(x - l) .. (x + 1)]

isPartNum :: [String] -> (Int, Int, Int) -> Bool
isPartNum xss n = or $ map isSymbol $ surrounds xss n

symbols :: [String] -> [[Int]]
symbols = foldr ((:) . symbolInLine) []

main = do
  input <- readFile inputPath >>= return . lines
  let ns    = numbers input
      parts = filter ((isPartNum input) . snd) ns
  putStrLn $ show $ sum $ map fst parts

