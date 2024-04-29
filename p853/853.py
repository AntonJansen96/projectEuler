#!/usr/bin/env python3

from tqdm import tqdm
from typing import Generator


def fibonacci(n: int) -> Generator[int, None, None]:
    """Generates t he Fibonacci sequence modulo n.

    Args:
        n (int): modulo n.

    Yields:
        int: Fibonacci term.
    """

    a, b = 0, 1
    while True:
        yield a
        a, b = b % n, (a + b) % n


def cycleCount(generator: Generator[int, None, None], maxCycle: int):
    lst = []
    for _ in range(2 * maxCycle):
        lst.append(next(generator))
        length = len(lst)
        for i in range(1, length // 2 + 1):
            if lst[:i] * (length // i) == lst[: i * (length // i)]:
                return i
    return None


assert cycleCount(fibonacci(3), 120) == 8
assert cycleCount(fibonacci(19), 120) == 18
assert cycleCount(fibonacci(38), 120) == 18
assert cycleCount(fibonacci(76), 120) == 18


def pisano(n: int) -> int:
    """Returns the Pisano period for n.

    Args:
        n (int): modulo n.

    Returns:
        int: Pisano period.
    """

    a = 0
    b = 1
    c = a + b
    for i in range(0, n * n):
        c = (a + b) % n
        a, b = b, c
        if a == 0 and b == 1:
            return i + 1

        if i + 1 > 120:
            return 0


assert pisano(3) == 8
assert pisano(19) == 18
assert pisano(38) == 18
assert pisano(76) == 18

total = 0
with tqdm(range(1, 10**9)) as pbar:
    for n in pbar:
        if pisano(n) == 120:
            total += n
            pbar.set_postfix({"total": total, "n": n}, refresh=True)

print(n)
