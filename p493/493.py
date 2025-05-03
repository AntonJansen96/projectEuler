#!/usr/bin/env python3

from scipy.special import comb as binom

probability = 7 * (1 - binom(60, 20) / binom(70, 20))
print(f"{probability:.9f}")
