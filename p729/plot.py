#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
from tqdm import tqdm

def F(x, P):
    for _ in range(P):
        x -= 1 / x  # x = f(x) = x - 1 / x
    return x

# PARAMS
P = 4
xstep = 0.0001





xlim = P - 1.8
iList = np.arange(-xlim, xlim, xstep)
xList = []
prev = None
threshold = 10  # Adjust as needed for your function

for i in tqdm(iList):
    if i == 0:
        xList.append(np.nan)
        prev = None
        continue
    val = F(i, P) - i
    if prev is not None and abs(val - prev) > threshold:
        xList.append(np.nan)  # Insert nan to break the line
    xList.append(val)
    prev = val

# After this loop, xList may be longer than iList if you append extra np.nan.
# Solution: Build both lists together, skipping i values when you insert nan.

xVals = []
yVals = []
prev = None

for i in tqdm(iList):
    if i == 0:
        xVals.append(i)
        yVals.append(np.nan)
        prev = None
        continue
    val = F(i, P) - i
    if prev is not None and abs(val - prev) > threshold:
        xVals.append(i)
        yVals.append(np.nan)
    xVals.append(i)
    yVals.append(val)
    prev = val

plt.figure(dpi=200)
plt.title(f"$P = {P}$")
plt.plot(xVals, yVals)
plt.hlines(y=0.0, xmin=-xlim, xmax=xlim, linestyles="--", color='black')
plt.vlines(x=0.0, ymin=-10, ymax=10, linestyles="--", color='black')
plt.axis([-xlim, xlim, -10, 10])
plt.xlabel("$a_0$")
plt.ylabel("")
plt.show()
