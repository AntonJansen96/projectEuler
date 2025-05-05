#!/usr/bin/env python3

from science.euler.primes import Primes

primes = Primes.sieve(5000)

maxsum = 0
maxcount = 0
for ii in range(0, len(primes)):

    sum = 0
    count = 0
    for jj in range(ii, len(primes)):

        sum += primes[jj]
        count += 1

        if sum > 1000000:
            break

        if Primes.isprime(sum) and count > maxcount:
            maxsum, maxcount = sum, count
            print(maxsum, maxcount)
