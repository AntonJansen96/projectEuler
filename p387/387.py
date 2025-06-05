#!/usr/bin/env python3

from science.euler import Primes, sumDigits

p = Primes()

def check_conditions(num: int) -> bool:

    # Number is prime, and ...
    if not p.isprime(num):
        return False

    # When we truncate the last digit
    num = int(str(num)[:-1])

    # We get a Harshad number...
    digitsum = sumDigits(num)
    if not (num % digitsum == 0):
        return False

    # That is strong...
    if not p.isprime(int(num / digitsum)):
        return False

    # And also right-truncatable
    trunc = str(num)
    while len(trunc) > 1:
        trunc = trunc[:-1]
        num = int(trunc)
        if not (num % sumDigits(num) == 0):
            return False
    
    return True

assert check_conditions(2011)

array = []  # debug
for num in range(1, 10_000):
    if num >= 10 and check_conditions(num):
        array.append(num)

print(array)
assert sum(array) == 90619

# Generate all right-truncatable Harshad numbers up to limit 10^13
RT_harshad = [1, 2, 3, 4, 5, 6, 7, 8, 9]
old = [1, 2, 3, 4, 5, 6, 7, 8, 9]

for _ in range(1, 13):

    new = []
    for num in old:
        for digit in range(0, 10):
            y = num * 10 + digit
            if (y % sumDigits(y) == 0):
                new.append(y)

    RT_harshad += new
    old = new

print(f"\n* There are {len(RT_harshad)} right-truncatable Harshad numbers < 10^13")
# print(RT_harshad[:100])

# We only want the strong RT-Harshad numbers...
strong_RT_harshad = []
for num in RT_harshad:
    if p.isprime(int(num / sumDigits(num))):
        strong_RT_harshad.append(num)

print(f"* There are {len(strong_RT_harshad)} strong right-truncatable Harshad numbers < 10^13")
# print(strong_RT_harshad[:100])

# And now we only the "strong RT-harshad primes"...
strong_RT_harshad_primes = []
for num in strong_RT_harshad:
    for digit in range(0, 10):
        y = num * 10 + digit
        if p.isprime(y):
            strong_RT_harshad_primes.append(y)

print(f"* There are {len(strong_RT_harshad_primes)} strong right-truncatable Harshad primes < 10^14:\n")
print(strong_RT_harshad_primes)
print(f"\n* solution = {sum(strong_RT_harshad_primes)}")
