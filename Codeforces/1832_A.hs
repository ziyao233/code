isNewPal :: String -> Bool

isNewPal xs = let
        letters = take (div (length xs) 2) xs
        in not $ and $ map (== (head letters)) $ tail letters

solution xs = if (isNewPal xs) then "yes" else "no"

main = do
        count <- getLine
        let
                action = getLine >>= (putStrLn . solution)
                actions = take (read count) $ repeat action
                in foldl (>>) (return ()) actions
