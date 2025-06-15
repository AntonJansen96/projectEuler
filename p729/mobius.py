#!/usr/bin/env python3

from sympy import mobius, divisors

def a(P):
    return sum(mobius(d) * (2**(P // d) - 2) for d in divisors(P))

print(sum([a(P) for P in range(2, 25 + 1)]))
