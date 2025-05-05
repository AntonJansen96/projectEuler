#!/usr/bin/env python3

from science.euler import genPartitions, genperms
from science.euler.utility import list2num

# Generate the possible allowed numbers

parts = {}
for number in range(1, 10):
    parts[number] = list(genPartitions(number))[:-1]

# print(parts)
# now we add the number itself to the partition
for number in range(1, 10):

    if number == 1:
        parts[number] = [[1, 1, 0]]

    else:
        for arr in parts[number]:
            arr += [number]
        
        parts[number] += [[number, number, 0]]  # 

# print(parts)

total = 0
for key in parts:
    for array in parts[key]:
        if len(array) <= 3:
            print(sorted(array, reverse=True), list(genperms(array, unique=True)))
            for perm in genperms(array, unique=True, asint=True):
                total += perm
print(total)




# print(list(genPartitions(9)))

# 9
# 8
# 7
# 6
# 5  -> [1 1 1 1 1], []
# 4  -> [1 1 1 1], [1 1 2], [2 2], [3 1]
# 3  -> [1 1 1], [1 2]
# 2  -> [1 1]
# 1  -> x 