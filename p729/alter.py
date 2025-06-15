#!/usr/bin/env python3

import matplotlib.pyplot as plt
import mpmath
import numpy as np
from sympy import symbols, nsolve

mpmath.mp.dps = 50

def naive(a, P):
    array = P * [0]
    for idx in range(P):
        array[idx] = a
        b = a - 1 / a
        a = b
    return array

################################################################################

SArray = []
Slim = 3

for S in range(2, Slim + 1):
# for S in [10]:

    x = symbols('x')
    lhs = x - 1 / x
    for _ in range(1, S):
        lhs = lhs - 1 / lhs

    solutions = set()
    for hint in np.arange(0, 5, 0.01):
        try:
            sol = float(nsolve(lhs - x, x, hint))
            solutions.add(sol)
            solutions.add(-sol)
        except (ValueError, ZeroDivisionError):
            pass
    print(S, len(list(solutions)), sorted(list(solutions)))

    count = 0
    for a0 in solutions:
        seq = naive(a0, S)
        seq = naive(a0, S)
        rang = max(seq) - min(seq)
        # print(rang, seq) # debug
        count += rang

    SArray.append(count)

    # print(f"S({S}) = {sum(SArray):.4f}")

# print(f"{sum(SArray):.4f}")
