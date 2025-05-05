#!/usr/bin/env python3

import random

from science.euler import Primes, gcd
from tqdm import tqdm

primeDict = {}
for num in range(1, 501):
    primeDict[num] = Primes.isprime(num)

# random.seed(42)

count = 0
target = "PPPPNNPPPNPPNPN"

for _ in tqdm(range(10)):

    for startpos in range(1, 501):

        pos = startpos
        good = True

        for idx in range(0, 15):

            # Just before jumping to the next square -> croak
            if primeDict[pos]:
                char = random.choice(['P', 'P', 'N'])
            else:
                char = random.choice(['P', 'N', 'N'])

            if char != target[idx]:
                good = False
                break

            # Jump to the next square
            if pos == 1:
                pos = 2
            elif pos == 500:
                pos = 499
            else:
                pos += random.choice([1, -1])

        if good:
            count += 1

print(count)


def reduce(p: int, q: int):
    factor = gcd(p, q)
    return p // factor, q // factor



q = 2**14 * 3**15

p, q = reduce(123, q)
print(f"{p}/{q}")

