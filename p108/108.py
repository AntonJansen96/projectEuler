#!/usr/bin/env python3

# First I tried the code using Python Fractions below.
# Then I noticed that sequence follows A018892, and found that
# a(n) is the number of divisors of n^2 that are <= n; e.g., a(12) counts
# these 8 divisors of 12: 1,2,3,4,6,8,9,12.

# from fractions import Fraction

# for n in range(1, 21):
#     distinct = 0
#     stop = False

#     xlim = 2 * n
#     ylim = int(Fraction(1, Fraction(1, n) - Fraction(1, n + 1)))

#     for x in range(n, xlim + 1):

#         if stop:
#             break

#         for y in range(x, ylim + 1):

#             if Fraction(1, x) + Fraction(1, y) == Fraction(1, n):
#                 distinct += 1

#                 # print(f"1/{x} + 1\{y} = 1/{n}")

#             if x == 2 * n and y == 2 * n:
#                 stop = True
#                 break

#     print(n, distinct)

from science.euler import Primes
from cProfile import run

p = Primes()


def func():

    n = 1
    while True:

        count = 0
        for divisor in p.factors(n * n):
            if divisor <= n:
                count += 1

        if count > 1000:
            print(n)
            break

        n += 1


run("func()")

# 180180. Took ~30s on M1.
