#!/usr/bin/env python3

from typing import Generator
from math import comb
import itertools


def genpascalrow(n: int) -> Generator[int, None, None]:
    for m in range(n):
        yield comb(n - 1, m)


def genPascalTriangle(rows: int) -> Generator[int, None, None]:
    result = [1]
    for _ in range(rows):
        yield from result
        result = [
            x + y
            for x, y in zip(itertools.chain([0], result), itertools.chain(result, [0]))
        ]


if __name__ == "__main__":

    # for row in range(1, 1001):
    #     count = 0
    #     for val in genpascalrow(row):
    #         if val % 7 != 0:
    #             count += 1
    #     print(f"row {row:3d}  {row // 70},{row // 7},{row % 7} {count:3d}")
    #     if row % 7 == 0:
    #         print()
   

    # header = True
    # num = 1
    # incr = 1
    # x = 1
    # y = 1
    # for row in range(1, 999 + 1):

    #     if header:
    #         print("row  num  incr   x    y")
    #         header = False
    #     print(f"{row:3d}  {num:3d}  {incr:3d}  {x:3d}  {y:3d}")

    #     num += incr

    #     if row % 7 == 0:
    #         header = True

    #         if incr % 7 == 0:

    #             x += 1
    #             incr = x
    #         else:
    #             incr += x

    #         num = incr
    #         print()


    num = 1
    row = 0

    a = 1
    b = 1
    c = 1
    d = 1
    for _ in range(1, 400 + 1):
        row += 1

        print(f"{row:3d}  {num:3d}  |  {a:3d}  {b:3d}  {c:3d}  {d:3d}")

        num += b

        if a % 7 == 0:
            a = 0

            if b % 7 == 0:
                b = 0

                c += 1
                b = c
            
            else:
                b += c

            num = b
            print()

        a += 1
