#!/usr/bin/env python3

from math import comb
from typing import Generator
from science.euler.primes import Primes

p = Primes()


def squarefree(num: int) -> bool:
    """Checks if a number is square-free. A positive integer n is called
    square-free if no square of a prime divides n.
    This is the case when it's prime decomposition holds no repeated factors.
    See https://oeis.org/A005117 and https://en.wikipedia.org/wiki/Square-free_integer.

    Args:
        num (int): number.

    Returns:
        bool: True if the number is squarefree, False otherwise.
    """

    pfactors = p.primefactors(num)
    return len(pfactors) == len(set(pfactors))


def genpascalrow(n: int) -> Generator[int, None, None]:
    """Yields the numbers in the nth row of Pascal's triangle.

    Args:
        n (int): row number.

    Yields:
        int: numbers in the nth row of Pascal's triangle.
    """

    for m in range(n):
        yield comb(n - 1, m)


count = 0
uniques = set()

for row in range(1, 52):
    for val in genpascalrow(row):
        uniques.add(val)

for num in uniques:
    if squarefree(num):
        count += num

print(count)

# 34029210557338. Runs in a few ms.
