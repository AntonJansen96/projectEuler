#!/usr/bin/env python3

from science.euler.primes import Primes

p = Primes()

count = 0
current = len(p.factors(1))

for num in range(2, 10**7):

    next = len(p.factors(num))

    if next == current:
        count += 1

    current = next

print(count)
