#!/usr/bin/env python3

from tqdm import tqdm
from math import log, exp
from science.euler import gcd, isCoprime, lastNdigits
from science.euler import Primes

p = Primes()

def F(N: int) -> int:
    """Smallest positive integer that is not comprime to any integer n <= N
    whose least significant digit is 3.
    """

    selected = []
    for n in range(1, N + 1):
        if n % 10 == 3 and p.isprime(n):
            selected.append(n)

    print(selected)

    prod = 1
    for num in selected:
        prod *= num
    return prod
    # for idx in tqdm(range(0, len(selected)), desc="computing F(N)"):
    #     good = True
    #     prod *= selected[idx]
    #     # print(idx, prod)
    #     for y in selected[idx:]:
    #         if isCoprime(prod, y):
    #             good = False
    #             break
    #     if good:
    #         return prod

    # x = 1
    # while True:
    #     good = True
    #     for y in selected:
    #         if isCoprime(x, y):
    #             good = False
    #             break
    #     if good:
    #         return x
    #     x += 1

assert F(40) == 897
assert round(log(F(40)), 6) == 6.799056

print(round(log(F(2800)), 7))
# assert round(log(F(2800)), 6) == 715.019337

# print(Primes().factors(40))
# print(Primes().primefactors(40))

print(Primes().factors(897))
print(Primes().primefactors(897))
