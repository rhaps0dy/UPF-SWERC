import Data.Function
import Data.Array

newtype Graph = Graph {unInner :: (Int, Array Int [Int])} deriving (Show, Eq)
instance Read Graph where
    readsPrec priority s =
        let [(nNodes, s')] = readsPrec priority s
            [(iniNode, s'')] = readsPrec priority s'
            initArr = array (1, nNodes) $ zip [1 .. nNodes] (repeat [])
            readNext arr str
                | indices arr == [] = (arr, "")
                | ind == 0          = (arr, str'')
                | otherwise         = readNext (arr // [(ind, node:(arr!ind))]) str''
                where [(ind, str')] = readsPrec priority str
                      [(node, str'')] = readsPrec priority str'
            (arr, str) = readNext initArr s''
        in  if nNodes == 0 then [(Graph (1, initArr), "")] else [(Graph (iniNode, arr), str)]


readSeveral :: Read a => String -> [a]
readSeveral = fun []
    where fun l "" = reverse $ tail l
          fun l s  = fun (e:l) s'
              where [(e, s')] = readsPrec 1 s

max' (a, b) (c, d)
    | a > c = (a, b)
    | a < c = (c, d)
    | b < d = (a, b)
    | b > d = (c, d)
    | otherwise = (a, b)

maxPath :: Graph -> (Int, Int)
maxPath (Graph (ind, arr))
    | indices arr == [] = (0, 0)
    | arr!ind == []     = (0, ind)
    | otherwise         = foldl max' (0, 0) (map fun (arr!ind))
    where fun i = let (l, i') = maxPath (Graph (i, arr))
                  in  (l+1, i')

showCase len ((i, ini), (a, b)) = "Case " ++ show i ++ ": The longest path from " ++
    show ini ++ " has length " ++ show a ++ ", finishing at " ++ show b ++
    ".\n" ++ if i == len then "" else "\n"

main = do
    c <- getContents
    let a = readSeveral c :: [Graph]
        l = zip (zip [1 ..] (map (fst . unInner) a)) $ map maxPath a
        str = concat $ map (showCase (length l)) l
    putStr str
