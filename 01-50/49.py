#!/usr/bin/env python3

from science.euler import numDigits
from science.euler.primes import Primes
from science.euler.combinatorics import genperms, gencombs
from science.euler.utility import num2list

for prime in [val for val in Primes.sieve(10000) if numDigits(val) == 4]:

    validperms = set()
    for perm in genperms(num2list(prime), asint=True):
        if Primes.isprime(perm) and numDigits(perm) == 4:
            validperms.add(perm)

    for comb in gencombs(validperms, 3):
        if comb[0] != 1487 and comb[1] - comb[0] == comb[2] - comb[1]:
            print(comb, 10**8 * comb[0] + 10**4 * comb[1] + comb[2])
            exit(0)
