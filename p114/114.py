#!/usr/bin/env python3

from science.euler.combinatorics import genPartitions, genperms


def solver(N: int):

    count = 0

    for partition in genPartitions(N):

        # Filter out all partitions that contain a block of length 2,
        # and all partitions without any gray squares (these will by
        # definition have two red blocks touching...)
        if (2 in partition) or (1 not in partition and len(partition) != 1):
            continue

        # Speedup: filter out all partitions that contains too many numbers != 1
        # so they will never be valid anyway.
        ones = partition.count(1)
        other = len(partition) - ones
        if other > ones + 1:  # We need at least #(others - 1) ones (e.g. 3 1 3 1 3).
            continue

        # For all the unique permutations of the partition...
        for uperm in genperms(partition, unique=True):

            # ... count it as valid if there are no colored blocks touching.
            skip = False
            for idx in range(0, len(uperm) - 1):
                if uperm[idx] != 1 and uperm[idx + 1] != 1:
                    skip = True
                    break
            if not skip:
                count += 1
            # ................

    return count


assert solver(7) == 17
assert solver(10) == 72
assert solver(20) == 8855
