#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt


def numroots(yy):
    count = 0
    for i in range(0, len(yy) - 1):
        if (yy[i] > 0 and yy[i + 1] < 0) or (yy[i] < 0 and yy[i + 1] > 0):
            count += 1
    return count


def f(x):
    return x * np.sin(x**2)


a = 0
b = 20
dt = 0.0001

xx = np.arange(a, b + dt, dt)
yy = [f(x) for x in xx]

print(f"{numroots(yy)} roots detected in interval [{a}, {b}]")

plt.hlines(y=0, xmin=a, xmax=b, linestyles="--", color="black")
plt.plot(xx, yy)
plt.xlim(a, b)
plt.show()
