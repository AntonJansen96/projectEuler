#!/usr/bin/env python3

from science.euler import Primes
from science.euler.combinatorics import gencombs
from tqdm import tqdm

p = Primes()

# Primes less than 100.
primes = p.sieve(100)
print(primes)

# basis numbers (all combs of [4 primes < 100])
gen = list(gencombs(primes, 4))
array = []
for x in gen:
    array.append(x[0] * x[1] * x[2] * x[3])
print(len(array))

lim = 10_000_000_000

# Integers less than lim that can be made from basis numbers
sel = []
for num in array:
    if num < lim:
        sel.append(num)
sel = sorted(sel)
# print(len(sel), sel)

# "multiplicity"
count = len(sel)
for num in tqdm(sel):
    x = num
    while True:
        x += num
        if x > lim:
            break
        else:
            count += 1
print(count)

# 1852819549 voor 10^10 in 3min19
