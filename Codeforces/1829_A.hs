differNum :: String -> String -> Int
differNum [] [] = 0
differNum (a : as) (b : bs) = (if a == b then 0 else 1) + differNum as bs

main = do
        count <- getLine
        let
                action = getLine >>= (print . differNum "codeforces")
                actions = take (read count) $ repeat action
                in foldl (>>) (return ()) actions
