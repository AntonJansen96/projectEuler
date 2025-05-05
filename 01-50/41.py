#!/usr/bin/env python3

from science.euler import genPanDigital
from science.euler.primes import Primes

largest = 0
for lim in range(1 ,10):
    for num in genPanDigital(1, lim):
        if Primes().isprime(num) and num > largest:
            largest = num
print(largest)
