#!/usr/bin/env python3
from itertools import product
from tqdm import tqdm

# Eliminating is too slow....

days = 30

total = 3**days
print(f"{total:.2e} total possible strings for {days} days")

prize = 0
for array in tqdm(product(range(3), repeat=days), total=total):
    # If late more than once, no prize.
    if array.count(2) > 1:
        continue

    # If absent for three consecutive days, no prize.
    noprize = False
    for idx in range(0, days - 2):
        if array[idx] == array[idx + 1] == array[idx + 2] == 1:
            noprize = True
            break
    if noprize:
        continue

    prize += 1

print(prize)

