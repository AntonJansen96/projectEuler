#!/usr/bin/env python3

from science.euler import sumDigits, fibonacci
from science.euler.fastmath import mulmod, powmod, modinverse


def s_naive(n):
    """Smallest number that has a digit sum of n."""
    x = 0
    while True:
        if sumDigits(x) == n:
            return x
        x += 1


def S_naive(k):
    "Sum of s(n)."
    total = 0
    for n in range(1, k + 1):
        total += s_naive(n)
    return total


assert s_naive(10) == 19
assert S_naive(20) == 1074

print([s_naive(x) for x in range(1, 21)])  # This is A051885
# These numbers are of the form s(n) = i * 10^j-1, with i = 1..9 and j >= 0.
# Using this, we can rewrite s(n) as:


def s(n):
    """Smallest number that has a digit sum of n."""
    i = n % 9 + 1
    j = n // 9
    return i * 10**j - 1


# Then, we can rewrite S(k) = sum_n=1^k(s(n)) as:


def S(k):
    "Sum of s(n)."
    q = (k + 1) // 9
    r = (k + 1) % 9
    return 45 * (10**q - 1) // 9 - 9 * q + (10**q * r * (r + 1)) // 2 - r


# Once we start running, we do find that this equation is quite slow.
# This is because of the extremely large numbers involved.
# We can rewrite (slightly faster):


def S(k):
    q = (k + 1) // 9
    r = (k + 1) % 9
    t = 10**q
    return (45 * (t - 1)) // 9 + (t * r * (r + 1)) // 2 - (9 * q + r)


# However still not cutting it. Luckily, answer is asked mod 10**9+7.
# This allows us to rewrite as follows:


def S(k):
    MOD = 1000000007

    def divmod(a: int, b: int, m: int) -> int:
        return mulmod(a, modinverse(b, m), m)

    q = (k + 1) // 9
    r = (k + 1) % 9
    t = powmod(10, q, MOD)

    part1 = mulmod(45, t - 1, MOD)
    part1 = divmod(part1, 9, MOD)

    part2 = mulmod(t, r, MOD)
    part2 = mulmod(part2, r + 1, MOD)
    part2 = divmod(part2, 2, MOD)

    part3 = - 9 * q - r

    return (part1 + part2 + part3) % MOD


assert all(S_naive(k) == S(k) for k in range(1, 21))

print([S(k) for k in range(1, 21)])

# Now that we have an efficient S(k) implementation, can do main problem:

x = fibonacci()
fibs = [next(x) for _ in range(91)][2:]
print(sum(S(f) for f in fibs) % 1000000007)

# 922058210, instant
