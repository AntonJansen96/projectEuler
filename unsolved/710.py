#!/usr/bin/env python3

from tqdm import tqdm
from sympy.utilities.iterables import multiset_permutations
from science.euler.utility import list2num
from science.euler import countDigits, isPalindrome


def partitionList(n):
    # base case of recursion: zero is the sum of the empty list
    if n == 0:
        yield []
        return
    # modify partitions of n-1 to form partitions of n
    for p in partitionList(n - 1):
        yield [1] + p
        if p and (len(p) < 2 or p[1] > p[0]):
            yield [p[0] + 1] + p[1:]


num = 4
count = 0

for part in partitionList(num):

    if not 2 in part:  # If there's no 2 we continue (speedup).
        continue

    found = []
    upermutations = multiset_permutations(part)

    for uperm in upermutations:
        if uperm == uperm[::-1]:
            if not uperm in found:
                count += 1
                found.append(uperm)
                print(part, uperm, count)
print(count)
