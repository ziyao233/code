module Main where

import qualified Text.ParserCombinators.Parsec as P

inputPath = "2.input"

-- (i, B, G, R)

data Color = Blue | Green | Red
instance Show Color where
  show Blue  = "blue"
  show Green = "green"
  show Red   = "red"
readColor ('b':'l':'u':'e':xs) =        [(Blue, xs)]
readColor ('g':'r':'e':'e':'n':xs) =    [(Green, xs)]
readColor ('r':'e':'d':xs) =            [(Red, xs)]
instance Read Color where
  readsPrec = const readColor

pItem :: P.Parser (Color, Int)
pItem = do
  P.skipMany1 P.space
  n <- P.many P.digit >>= return . read
  P.char ' '
  c <- P.many P.letter >>= return . read
  P.optional $ P.char ','
  return (c, n)

pSet :: P.Parser [(Color, Int)]
pSet = P.many pItem

pGame :: P.Parser (Int, [[(Color, Int)]])
pGame = do
  P.string "Game "
  i <- (P.many P.digit) >>= return . read
  P.char ':'
  xs <- P.sepBy pSet (P.char ';')
  return (i, xs)

fromRight' :: Show a => Either a b -> b
fromRight' (Left x)  = error $ show x
fromRight' (Right x) = x

parseGame :: String -> (Int, [[(Color, Int)]])
parseGame xs = fromRight' $ P.parse pGame "Game String" xs

isPossibleItem :: (Color, Int) -> Bool
isPossibleItem (Red, n)   = n <= 12
isPossibleItem (Blue, n)  = n <= 14
isPossibleItem (Green, n) = n <= 13

isPossibleTurn = and . map isPossibleItem
isPossibleGame = and . map isPossibleTurn . snd

main = do
  input <- readFile inputPath
  let games = map parseGame $ lines input
  putStrLn $ show $ sum $ map fst $ filter isPossibleGame games
