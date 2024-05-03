#!/usr/bin/env python3

from tqdm import tqdm
from science.euler.combinatorics import genPartitions, genperms


class Partitionclassifier:
    """Classifies a partition."""

    def __init__(self, part: list[int]):
        self.part = part
        self.ones = part.count(1)
        self.array = []
        self.multiplicity = 1

        for blocklen in range(3, 51):
            num = part.count(blocklen)
            if num > 0:
                self.array.append(num)

    def __eq__(self, other: "Partitionclassifier"):
        return self.array == other.array and self.ones == other.ones


def solver(N: int):

    count = 0
    distinct_partitions = []

    for partition in genPartitions(N):

        # ......................................................................
        # This block filters out invalid partitions. It filters out partitions
        # that contain a block of length 2, and partitions without any gray
        # squares (these will by definition have two red blocks touching).
        # It also filters out partitions that contain too many numbers != 1.

        if (2 in partition) or (1 not in partition and len(partition) != 1):
            continue

        ones = partition.count(1)
        other = len(partition) - ones
        if other > ones + 1:
            continue

        # ......................................................................
        # This block checks if partitions are equivalent to save a lot of time.
        classifier = Partitionclassifier(partition)

        found = False
        for idx in range(0, len(distinct_partitions)):
            if classifier == distinct_partitions[idx]:
                distinct_partitions[idx].multiplicity += 1
                found = True
                break

        if not found:
            distinct_partitions.append(classifier)
        # ......................................................................

    print(len(distinct_partitions))

    # Now we loop through all the distinct partitions, of which we already know
    # their multiplicity, and for each calculate the number of unique ways to
    # fill the row.
    for classifier in tqdm(distinct_partitions):

        # print(classifier.part, classifier.multiplicity)  # debug.

        # For all the unique permutations of the partition...
        for uperm in genperms(classifier.part, unique=True):

            # ..................................................................
            # This block checks if partitions are equivalent to save a lot of time.
            skip = False
            for idx in range(0, len(uperm) - 1):
                if uperm[idx] != 1 and uperm[idx + 1] != 1:
                    skip = True
                    break
            if not skip:
                count += classifier.multiplicity
            # ..................................................................

    return count


assert solver(7) == 17
assert solver(10) == 72
assert solver(20) == 8855

print(solver(30))
