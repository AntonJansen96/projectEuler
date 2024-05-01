#!/usr/bin/env python3

from tqdm import tqdm
from science.euler import fibonacci, sumDigits

# smallest number that has a digit sum of n.
digitsumdict = {}

for num in tqdm(range(1, 1000)):
    val = sumDigits(num)
    if val not in digitsumdict:
        digitsumdict[val] = num

print(digitsumdict)

total = 0
for n in range(1, 21):
    total += digitsumdict[n]

# print(total)

fibs = []
fibonacci = fibonacci()
for _ in range(1, 91):
    fibs.append(next(fibonacci))
fibs = fibs[2:]
print(fibs)


def s(n: int) -> int:
    pass


N = 1000

x = [i * 10**j - 1 for j in range(0, N // 10) for i in range(1, 10)]
x = [i % 1000000007 for i in x]
# print(x)
# print(sum(x[:21]))
