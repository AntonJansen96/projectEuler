#!/usr/bin/env python3

from science.euler.combinatorics import genPartitions, numperms

n = 50
count = 0

for partition in genPartitions(n):

    # Filter out all partitions that contain blocks > 4.
    skip = False
    for val in range(5, n + 1):
        if val in partition:
            skip = True
            break
    if skip:
        continue

    # Filter out the partitions that are mixing red and green.
    if 2 in partition and 3 in partition:
        continue

    # Filter out the partitions that are mixing red and blue.
    if 2 in partition and 4 in partition:
        continue

    # Filter out the partitions that are mixing green and blue.
    if 3 in partition and 4 in partition:
        continue

    # Filter out the partition with only gray squares.
    if sum(partition) == len(partition):
        continue

    ways = numperms(partition, unique=True)
    count += ways
    print(partition, ways)

print(count)

# 20492570929. ~ 400ms on M1.
