#!/usr/bin/env python3

from functools import lru_cache


@lru_cache(maxsize=None)
def nblocks(n):
    global m

    if 0 <= n <= (m - 1):
        return 1
    else:
        return nblocks(n - 1) + sum(nblocks(n - r - 1) for r in range(m, n)) + 1


m = 10
nblocks.cache_clear()
assert nblocks(56) == 880711

m = 10
nblocks.cache_clear()
assert nblocks(57) == 1148904

m = 50
nblocks.cache_clear()
n = 1
while True:
    if nblocks(n) > 10**6:
        print(n)
        break
    n += 1

# The function above is a function I found in the solutions of the problem 114.
# I modified it to calculate it with an arbitrary block cutoff length m
# Then simply do a while True loop until we hit 1'000'000.
# The answer is 168. Runs in ms.
