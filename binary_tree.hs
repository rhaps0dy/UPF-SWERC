mod_val :: Int
mod_val = 21092013

data UEntry = UEntry { left :: Int, right :: Int } deriving (Show)

process_insts :: String -> (String, Integer)
process_insts s = foldl f ("", 0) s
    where f ("", 0) 'U' = ("", 0)
          f (x:xs, len) 'U' = (xs, len-1)
          f (xs, len) c = (c:xs, len+1)

suffix_step :: ([UEntry], Int, Int, Char) -> ([UEntry], Int)
suffix_step (us, n, _, _) [] = (tail us, n)
suffix_step ((u:us), n, lastn, lastc) (x:xs)
    | x == 'U'  = suffix_step ((u:u:us), n, lastn, 'U')
    | otherwise = suffix_step (nextus, nextn, nextlastn, x)
    where nextlastn = if x == lastc then lastn else ((n + mod_val) - lastn + 1) `mod` mod_val
          nextn     = (n + nextlastn) `mod` mod_val
          nextus    = if x == 'R' then (UEntry (left u) n):us else (UEntry n (right u)):us
suffix_step ([], n, lastn, lastc) xs = suffix_step([(UEntry 0 0)], 1, 1, '_')


calc_suffixes s = f ([], 1, 1, '_') $ reverse s
    where
        f (us, n, _, _) [] = (us, n)
        f ((u:us), n, lastn, lastc) (x:xs)
            | x == 'U' = f (u:u:us, n, lastn, lastc) xs
            | x == lastc = if x=='R'
                then f ((UEntry (left u) n):us, (n+lastn) `mod` mod_val, lastn, x) xs
                else f ((UEntry n (right u)):us, (n+lastn) `mod` mod_val, lastn, x) xs
            | otherwise = if x=='R'
                then f ((UEntry (left u) n):us,
                    (n+((n+mod_val)-lastn+1) `mod` mod_val) `mod` mod_val,
                    ((n+mod_val)-lastn+1) `mod` mod_val, x) xs
                else f ((UEntry n (right u)):us,
                    (n+((n+mod_val)-lastn+1) `mod` mod_val) `mod` mod_val,
                    ((n+mod_val)-lastn+1) `mod` mod_val, x) xs
        f _ (x:xs)
            | x == 'U' = f ([(UEntry 0 0)], 1, 1, 'U') xs
            | x == 'L' = f ([], 2, 1, 'L') xs
            | x == 'R' = f ([], 2, 1, 'R') xs

