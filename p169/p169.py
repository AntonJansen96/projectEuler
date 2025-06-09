#!/usr/bin/env python3

from more_itertools import distinct_combinations
from functools import lru_cache

# First, code naive implementation to generate some terms.
def naive(n):

    # Generates all unique combinations of an array of elements.
    def unique_combinations(array):
        array = sorted(array)
        for r in range(len(array) + 1):
            yield from distinct_combinations(array, r)

    # Generates all possible factors of two <= n (twice, sorted).
    def genfactors(n):
        x = 0
        array = []
        while 2**x <= n:
            array.append(2**x)
            x += 1
        return sorted(array + array)

    # Count number of possible splits of the number.
    count = 0
    for comb in unique_combinations(genfactors(n)):
        if sum(comb) == n:
            count += 1
    return count

# We find Stern's diatomic series https://oeis.org/A002487.
print([naive(x) for x in range(0, 15)])

# Stern's diatomic series is given by:
# a(0) = 0
# a(1) = 1
# a(n) = a(2n)
# a(2n + 1) = a(n) + a(n + 1)

# 1. 
# a(n) = a(2n) -> a(n) = a(n // 2) (even n)

# 2. 
# a(2n + 1) = a(n) + a(n + 1) -> a(n) = a(2n + 1) - a(n + 1)
# set k = 2n + 1 -> n = (k - 1) // 2. Now:
# a((k - 1) // 2) = a(k) - a((k - 1) // 2 + 1)
# a(k) = a((k - 1) // 2) + a((k - 1) // 2 + 1) 
# a(n) = a((n - 1) // 2) + a((n - 1) // 2 + 1) (odd n)

@lru_cache() # memoization
def a(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    if n % 2 == 0:
        return a(n // 2)
    else:
        return a((n - 1) // 2) + a((n - 1) // 2 + 1)

n = 10**25
print(a(n + 1))
