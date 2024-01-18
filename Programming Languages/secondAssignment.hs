-- #1 "Main" Function
problem1 n = snd(unzip(dropEveryOther(zip[1..](getPrimes n))))
-- Drops every other element in a zipped list
dropEveryOther xs = [x | x <- xs, fst(x) `mod` 2 /= 0]
-- Get a bunch of prime numbers and then take the amount specified
getPrimes n = (take (n*2) [x | x <- [2..n*n], isPrime(x)])
-- Gets prime numbers (from lecture)
isPrime n = ip n [2..(isqrt(n))]
    where
    ip _ [] = True
    ip n (x:xs)
     |    n `mod` x == 0 = False
     |    otherwise = ip n xs

isqrt :: Integral i => i -> i
isqrt = floor . sqrt . fromIntegral

-- #2 "Main" Function
-- Pretty much just FibList but changed so that it only adds Fibonacci numbers that end in 3
problem2 n = (go n 1 1)
    where
    go n f s
     |    (f+s) > n = []
     |    otherwise = if last(show(f+s)) == '3' then (f+s) : go n s (f+s) else go n s (f+s)


-- #3 "Main" Function
problem3 n = [x | x <- [1..n], isMultOfFive x || length(getAllFactors x) == 3]
-- Gets all factors of a number
getAllFactors n = [x | x <- [1..n], n `mod` x == 0]
-- Checks if a number is a multiple of 5
isMultOfFive x = x `mod` 5 == 0

