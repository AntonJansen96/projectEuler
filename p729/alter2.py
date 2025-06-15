#!/usr/bin/env python3

import mpmath as mp

mp.dps = 50  # Arbitrary precision


def f(x):
    return x - 1 / x


def compose(f, x, P):
    for _ in range(P):
        x = f(x)
    return x


def find_periodic(P, x_min, x_max, step=0.001):
    F = lambda x: compose(f, x, P) - x
    roots = set()

    def round_mpf(x, digits=30):
        scale = mp.mpf(10) ** digits
        return mp.nint(x * scale) / scale

    xs = list(mp.arange(x_min, -step, step)) + list(mp.arange(step, x_max, step))
    for x0 in xs:
        try:
            root = mp.findroot(F, x0, solver='newton')
            root = round_mpf(root)
            roots.add(root)
        except (ZeroDivisionError, ValueError):
            continue

    return sorted(roots)

print(len(find_periodic(25, -10, 10)))