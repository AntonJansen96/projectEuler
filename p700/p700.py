#!/usr/bin/env python3

from tqdm import tqdm
from science.euler.fastmath import modinverse

a = 1504170715041707
b = 4503599627370517
a_inv = modinverse(a, b)

coinsum = 0

# First ascend: try the first 50'000'000 n and find the smallest x.

xx, nn = 10**20, 0

print("Ascending: trying the first 50'000'000 n.")
for n in tqdm(range(1, 50000000)):
    x = a * n % b
    if x < xx:
        coinsum += x
        xx = x
        nn = n

# Now we descend, we start at smallest x and go to 1, calculating every n.

coindict = {}
print("Descending: calculating n for every x < smallest.")
for x in tqdm(range(xx, 0, -1)):
    n = x * a_inv % b
    if n > nn:
        coindict[n] = x

print("Sorting resulting dictionary.")
coindict = dict(sorted(coindict.items()))

keys = list(coindict)
print("Make sure x is in descending order in the dictionary.")
for ii in tqdm(range(0, len(keys) - 1)):

    try:
        current = coindict[keys[ii]]
    except KeyError:
        continue

    for jj in range(ii + 1, len(keys)):

        next = coindict[keys[jj]]

        if next > current:
            del coindict[keys[jj]]
            continue

        break

print(coinsum + sum(coindict.values()))

# 1517926517777556
# Runs in ~ 1m on M1.
