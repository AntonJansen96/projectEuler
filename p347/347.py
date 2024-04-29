#!/usr/bin/env python3

from tqdm import tqdm
from science.euler import Primes

pp = Primes()

factorDict = {}
for num in tqdm(range(1, 10**7 + 1)):
    factors = pp.primefactors(num, multiplicity=False)
    if len(factors) == 2:
        factorDict[tuple(sorted(factors))] = num

print(sum(factorDict.values()))

# 11109800204052
# Runs in about 1 min on M1.
