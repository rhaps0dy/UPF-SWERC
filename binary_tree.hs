mod_val :: Int
mod_val = 21092013

data UEntry = UEntry { left :: Int, right :: Int } deriving (Show)

process_insts :: String -> String
process_insts s = foldl f "" s
    where f "" 'U' = ""
          f (x:xs) 'U' = xs
          f xs c = c:xs

suffix_step :: ([UEntry], Int, Int, Char) -> String -> ([UEntry], Int)
suffix_step ((u:us), n, _, _) [] = (us, n)
suffix_step ((u:us), n, lastn, lastc) (x:xs)
    | x == 'U'  = suffix_step ((u:u:us), n, lastn, lastc) xs
    | otherwise = suffix_step (nextus, nextn, nextlastn, x) xs
    where nextlastn = if x == lastc then lastn else ((n + mod_val) - lastn + 1) `mod` mod_val
          nextn     = (n + nextlastn) `mod` mod_val
          nextus    = if x == 'R' then (UEntry (left u) n):us else (UEntry n (right u)):us
suffix_step ([], n, lastn, lastc) xs = suffix_step ([(UEntry 0 0)], 1, 1, '_') xs

calc_n :: [UEntry] -> Int -> String -> Int
calc_n [] n _ = n
calc_n _ n [] = n
calc_n (u:us) n (x:xs) = calc_n us (n + 1 + newus) xs
	where newus = if x == 'R' then right u else left u

calc_result s t = calc_n (fst res) (snd res) (process_insts s)
	where res = suffix_step ([], 0, 0, '_') $ reverse t


