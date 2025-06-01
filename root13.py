#!/usr/bin/env python3

from decimal import Decimal, getcontext


def S(n: int, d: int) -> int:
    """Sum of the first d digits in the fractional part of the decimal expansion of sqrt(n)."""

    getcontext().prec = d + 5  # set desired precision (plus some buffer)
    x = Decimal(n).sqrt()

    start = False
    count = 0
    total = 0

    for char in str(x):

        if char == ".":
            start = True
            continue

        if start:
            total += int(char)
            count += 1

        if count == d:
            return total


assert S(2, 10) == 31
assert S(2, 100) == 481

print(S(13, 1000))
