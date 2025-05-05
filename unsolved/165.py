#!/usr/bin/env python3

from science.euler import sumDigits, numDigits


# NAIVE FOR VALIDATION AND TEST CASES ##################


def countNaive(digit: int):

    def checkNaive(num: int):

        for i in range(0, numDigits(num) - 2):

            split = int(str(num)[i : i + 3])

            if sumDigits(split) > 9:
                return False

        return True

    count = 0
    for num in range(10 ** (digit - 1), 10**digit):
        if checkNaive(num):
            count += 1

    return count


print(f"There are {countNaive(3)} 3-digit numbers")
print(f"There are {countNaive(4)} 4-digit numbers")
print(f"There are {countNaive(5)} 5-digit numbers")
# print(f"There are {countNaive(6)} 6-digit numbers")


# MAIN APPROACH ########################################


# Generate starting triplets.
trip_start = [num for num in range(100, 1000) if sumDigits(num) <= 9]

assert(len(trip_start) == countNaive(3))
print(trip_start)

# Unique last-two-digit possibilities
trip_start_t_u = sorted(list(set([str(x)[1:] for x in trip_start])))

print(trip_start_t_u, len(trip_start_t_u))

# Create dictionary

mydict1 = {}  # Key = last two digits, val = array of allowed next digits
mydict2 = {}  # Key = last two digits, val = array of allowed last two digits, left-shifted

for firsttwo in trip_start_t_u:
    array1 = []
    array2 = []
    for num in range(0, 10):
        trip = firsttwo + str(num)
        if sumDigits(int(trip)) <= 9:
            array1.append(trip)
            array2.append(trip[1:])
    mydict1[firsttwo] = array1
    mydict2[firsttwo] = array2

# print(mydict1)  # debug
# print(mydict2)  # debug


# Four digits


count = 0
for num in [str(x) for x in trip_start]:
    trunc = num[1:]
    count += len(mydict2[trunc])

assert(count == countNaive(4))


# Five digits


# count = 0
# for num in [str(x) for x in trip_start]:
#     trunc = num[1:]
    
#     print(num, trunc)
#     count2 = 0
#     for val in mydict2[trunc]:
#         count2 += len(mydict2[val])
#     count += count2

# print(count)

count = 0
num = ''
