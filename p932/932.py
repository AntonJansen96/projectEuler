#!/usr/bin/env python3

total = -1  # ignore (a, b) = (0, 1) solution.

for bb in range(1, 10**8):

    n = len(str(bb))
    m = 10**n

    # Input for ABC formula
    a = 1
    b = 2 * bb - m
    c = bb * bb - bb
    d = b * b - 4 * a * c

    if d >= 0:  # ignore non-existant solutions

        d_sqrt = d**0.5  # ignore non-integer solutions
        if (d_sqrt) == int(d_sqrt):
            d_sqrt = int(d_sqrt)

            aa = (-b - d_sqrt) // (2 * a)
            print("a, b = ", aa, bb)
            total += aa * m + bb

            aa = (-b + d_sqrt) // (2 * a)
            print("a, b = ", aa, bb)
            total += aa * m + bb

print(total)
