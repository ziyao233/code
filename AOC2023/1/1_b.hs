module Main where

import Control.Monad
import Data.Char as C
import Data.List as L
import Data.Maybe
import Debug.Trace

inputPath = "1.input"

pairs = [
 ('1', "one"),
 ('2', "two"),
 ('3', "three"),
 ('4', "four"),
 ('5', "five"),
 ('6', "six"),
 ('7', "seven"),
 ('8', "eight"),
 ('9', "nine") ]
revpairs = map (\(a, b) -> (b, a)) pairs

normalize :: String -> String
normalize "" = ""
normalize (x:xs) = (fromMaybe [x] $ lookup x pairs) ++ (normalize xs)

prefixNum :: String -> Maybe Char
prefixNum xs = listToMaybe $ mapMaybe (flip f xs) revpairs
  where f (w, c) xs = if isPrefixOf w xs then Just c else Nothing

fstNum :: String -> Char
fstNum xs@(x:xs') = fromMaybe (fstNum xs') $ prefixNum xs

sndNum :: String -> Char
sndNum "" = ' '
sndNum xs@(x:xs')
  | r == ' '  = fromMaybe ' ' $ prefixNum xs
  | otherwise = r
  where r = sndNum xs'

procLine :: String -> Int
procLine xs = read $ fstNum xs' : sndNum xs' : []
  where xs' = normalize xs

main = do
  input <- readFile inputPath
  putStrLn $ show $ sum $ map procLine $ lines input
