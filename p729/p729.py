#!/usr/bin/env python3

from sympy import sqrt
import numpy as np

def naive(a, P):
    array = P * [0]
    for idx in range(P):
        array[idx] = a
        b = a - 1 / a
        a = b
    return array

def array_range(array):
    return max(array) - min(array)



import mpmath
from sympy import symbols, Eq, nsolve
mpmath.mp.dps = 30  # 20 decimal places

x = symbols('x')
lhs = x - 1 / x
lhs = lhs - 1 / lhs
lhs = lhs - 1 / lhs

solutions = set()
for hint in np.arange(-2, 2, 0.01):
    try:
        sol = float(nsolve(lhs - x, x, hint))
        solutions.add(sol)
    except ValueError:
        pass
print((solutions))




count = 0
P = 3
# periodics = [1 / sqrt(2), - 1 / sqrt(2)]
periodics = list(solutions)
for a0 in periodics:
    seq = naive(a0, P)
    rang = array_range(seq)
    print(rang, seq)
    count += rang
print(f"S({P}) = {count} ≈ {float(count):.4f}")

# This is all easy enough. The real question is, for given P, how do we find
# 'periodics', that is, the different a0 that will give a P-periodic sequence?
