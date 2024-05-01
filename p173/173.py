#!/usr/bin/env python3

t = 10**6

count = 0
for x in range(3, t // 4 + 2):
    for y in range(x - 2, 0, -2):

        if x * x - y * y <= t:
            count += 1
        else:
            break

print(count)
# 1572729. Runs in a few ms.
