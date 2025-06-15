#!/usr/bin/env python3

import numpy as np
from scipy.optimize import newton
from tqdm import tqdm


def f(x):
    return x - 1 / x


def f_prime(x):
    return 1 + 1 / x**2


def composed_f(x, P):
    for _ in range(P):
        x = f(x)
    return x


def composed_f_derivative(x, P):
    df = 1.0
    for _ in range(P):
        df *= f_prime(x)
        x = f(x)
    return df


def G(x, P):
    return composed_f(x, P) - x


def G_der(x, P):
    return composed_f_derivative(x, P) - 1


def find_roots(P, xlim=7.0, xstep=0.00001, tol=1e-12):
    roots = []
    seen = set()
    for hint in tqdm(np.arange(xstep, xlim, xstep)):
        try:
            root = newton(G, hint, fprime=G_der, args=(P,), tol=tol, maxiter=100)
            if root > 10:
                continue
            key = round(root, int(-np.log10(tol)))
            if key not in seen:
                seen.add(key)
                roots.append(root)
                roots.append(-root)
        except (ZeroDivisionError, RuntimeError, OverflowError):
            continue
    return sorted(roots)


if __name__ == "__main__":
    P = 25
    xlim = 7.0 # seems reasonable from plot.py with xstep = 0.00001
    xstep = 0.0001
    tol = 1e-12

    roots = find_roots(P, xlim, xstep, tol)
    for r in roots:
        print(f"{r:.15f}")
    print(f"\nFound {len(roots)} unique roots for P = {P}")
