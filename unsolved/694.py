#!/usr/bin/env python3

from science.euler import Primes
from tqdm import tqdm
p = Primes()

def cubefull(n: int) -> bool:
    if n == 1:
        return True
    factors = p.primefactors(n, multiplicity=False)
    # print(n, factors)
    for prime in factors:
        if n % (prime * prime * prime) != 0:
            return False
    return True

lookup = []
print("Creating lookup table")
for i in range(1, 10**4 + 1):
    lookup.append(int(cubefull(i)))
lookup = [0] + lookup

def S(lim: int) -> int:
    count = 0
    for num in range(1, lim + 1):
        for divisor in p.factors(num):
            count += lookup[divisor]
    return count

for x in range(1, 101):
    print(x, S(x), p.primefactors(x))
uplim = 10
cubed1 = []
primes = p.sieve(uplim)
for prime in primes:
    x = prime * prime * prime
    while x < uplim**3:
        cubed1.append(x)
        x *= prime

for ii in tqdm(range(0, len(cubed1))):
    for jj in range(1, len(cubed1) - 1):
        x = cubed1[ii] * cubed1[jj]
        if x < uplim**3:
            cubed1.append(x)

cubed1 = [1] + sorted(list(set(cubed1)))
print(cubed1)
