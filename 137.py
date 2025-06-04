#!/usr/bin/env python3

# Look up sequences on OEIS where 74049690 is term 10.
# Found https://oeis.org/A081018
# Here, wee see that A081018(n) = F(2n) * F(2n + 1)
# To solve, simply implement:

from science.euler import fibonacci

x = fibonacci()
F = [next(x) for _ in range(1, 40)]
print(F[2 * 15] * F[2 * 15 + 1])

# Minimalist version:

a, b = 0, 1
for _ in range(2 * 15):
    a, b = b, a + b
print(a * b)
