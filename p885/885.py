#!/usr/bin/env python3

from science.euler.combinatorics import numperms
from science.euler.utility import list2num


def ff(d):
    return int(''.join(sorted(list(filter(lambda x: x != '0', str(d))))))

assert ff(3403) == 334
assert sum([ff(num) for num in range(1, 10**1)]) == 45
assert sum([ff(num) for num in range(1, 10**5)]) == 1543545675

# 1 45 
# 2 3456 
# 3 254475 
# 4 19457757 
# 5 1543545675
# 6 125796691845

count = 0
total = 0

for a in range(0, 10):
    for b in range(a, 10):
        for c in range(b, 10):
            for d in range(c, 10):
                for e in range(d, 10):
                    for f in range(e, 10):
                        for g in range(f, 10):
                            for h in range(g, 10):
                                for i in range(h, 10):
                                    for j in range(i, 10):
                                        for k in range(j, 10):
                                            for l in range(k, 10):
                                                for m in range(l, 10):
                                                    for n in range(m, 10):
                                                        for o in range(n, 10):
                                                            for p in range(o, 10):
                                                                for q in range(p, 10):
                                                                    for r in range(q, 10):
                                                                        array = [a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r]
                                                                        total += list2num(array) * numperms(array, unique=True)
                                                                        count += 1

print(count, total % 1123455689)
# 827850196
# ~ 17s on i5 7600k


# These nested for-loops can be written a lot shorter by using:



# from itertools import combinations_with_replacement

# total = 0

# for array in combinations_with_replacement(range(10), 18):
#     total += list2num(array) * numperms(array, unique=True)

# print(total % 1123455689)



# count = 0
# total = 0
# for i in range(0, 10):
#     for j in range(i, 10):
#         for k in range(j, 10):
#             for l in range(k, 10):
#                 for m in range(l, 10):
#                     for n in range(m, 10):

#                         array = [i, j, k, l, m, n]
#                         total += list2num(array) * numperms(array, unique=True)
#                         count += 1

# print(count, total)
