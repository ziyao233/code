longestSpace :: [Char] -> Int
longestSpace = let
        next (hMax, _) '1' = (hMax, 0)
        next (hMax, nMax) '0' = let
                n = nMax + 1
                in ((max hMax n), (n))
        in fst . foldl next (0, 0)

main = do
        count <- getLine
        let
                action = (getLine >> return ()) >> getLine >>=
                         (print . longestSpace . concat . words)
                actions = take (read count) $ repeat action
                in foldl (>>) (return ()) actions
