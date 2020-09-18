# 72 - COUNTING FRACTIONS

# Consider the fraction, n/d, where n and d are positive integers.
# If n<d and HCF(n,d)=1, it is called a reduced proper fraction.

# If we list the set of reduced proper fractions for d <= 8 in ascending order of size, we get:

# 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8

# It can be seen that there are 21 elements in this set.

# How many elements would be contained in the set of reduced proper fractions for d <= 1,000,000?

# NAIVE WAY I BRUTE-FORCED IT IN CYTHON

def gcd(a,b):
    while b != 0:
        a, b = b, a % b
    return a

limit = 10**3
count = 0

for n in range(1, limit + 1):
    for d in range(1, limit + 1):
        if n < d and gcd(n, d) == 1:
            count += 1

print(count)
