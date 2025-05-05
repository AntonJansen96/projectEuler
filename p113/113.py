#!/usr/bin/env python3

def func(n: int):
    # https://oeis.org/A204692
    from scipy.special import comb
    return comb(n + 10, 10, exact=True) + comb(n + 9, 9, exact=True) - 10*n - 2

print(func(100))
