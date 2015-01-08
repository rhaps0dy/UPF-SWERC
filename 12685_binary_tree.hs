import Control.Monad

mod_val :: Int
mod_val = 21092013

data UEntry = UEntry { left :: Int, right :: Int } deriving (Show)
data Inst = R | L | U deriving (Show, Eq)

insts :: String -> [Inst]
insts s = map getInst s
    where getInst 'U' = U
          getInst 'L' = L
          getInst 'R' = R

calc_location :: [Inst] -> [Inst]
calc_location ds = foldl f [] ds
    where f [] U = []
          f (i:is) U = is
          f is i = i:is

suffix_step :: [UEntry] -> Int -> Int -> Inst -> [Inst] -> ([UEntry], Int)
suffix_step (u:us) n _ _ [] = (us, n)
suffix_step (u:us) n lastn lasti (U:is) = suffix_step (u:u:us) n lastn lasti is
suffix_step (u:us) n lastn lasti (i:is) = suffix_step nextus nextn nextlastn i is
    where nextlastn = if i==lasti then lastn else ((n + mod_val) - lastn + 1) `mod` mod_val
          nextn     = (n + nextlastn) `mod` mod_val
          nextus    = if i == R then (UEntry (left u) n):us else (UEntry n (right u)):us

calc_suffix = suffix_step [(UEntry 0 0)] 1 1 U

calc_n :: [UEntry] -> Int -> [Inst] -> Int
calc_n [] n _ = n
calc_n _ n [] = n
calc_n (u:us) n (R:is) = calc_n us (n + 1 + (left u)) is
calc_n (u:us) n (L:is) = calc_n us (n + 1 + (right u)) is

result s t = calc_n us n (calc_location (insts s))
    where (us, n) = calc_suffix (reverse (insts t))

one_tree :: Int -> Int -> IO ()
one_tree total i
    | i == total = return ()
    | otherwise = do
        s <- getLine 
        t <- getLine
        putStrLn $ "Case " ++ show (i+1) ++ ": " ++ show (result s t)
        one_tree total (i+1)

main = do
    total <- getLine
    one_tree (read total) 0
