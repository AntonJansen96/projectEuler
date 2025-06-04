#!/usr/bin/env python3

from science.euler import genAllTriples


def check(a, b, c):
    # surf_open = (c * c - 2 * a * b)
    return (c * c) % (c * c - 2 * a * b) == 0


if __name__ == "__main__":
    # assert_example(3, 4, 5)
    # assert_example(5, 12, 13)

    count = 0
    x, y, z = genAllTriples(1_000_000)
    for idx in range(len(x)):
        a, b, c = x[idx], y[idx], z[idx]
        if a > b and a > c:
            if check(b, c, a):
                count += 1
        elif b > a and b > c:
            if check(a, c, b):
                count += 1
        else:
            if check(a, b, c):
                count += 1
    print(count)
