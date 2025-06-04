#include <iostream>
#include <cmath>

// Helper function for generating triples.
bool isCoprime(size_t a, size_t b)
{
    if (((a | b) & 1) == 0)
        return false;

    while (b)
        b ^= a ^= b ^= a %= b;

    return a == 1;
}

// Checks whether we can fill a square with the holes.
bool check(size_t a, size_t b, size_t c)
{
    if (c > a && c > b)
        return (c * c) % (c * c - 2 * a * b) == 0;
    else if (b > a && b > c)
        return (b * b) % (b * b - 2 * a * c) == 0;
    else
        return (a * a) % (a * a - 2 * b * c) == 0;
}

// Main code.
int main()
{
    size_t const lim = 100'000'000;
    size_t count = 0;
    size_t a, b, c, k;

    for (size_t m = 1; m < sqrt(lim); ++m)
        for (size_t n = m + 1; n < sqrt(lim); ++n)
            if (!(m & 1 && n & 1) && isCoprime(m, n))
            {
                a = n * n - m * m;
                b = 2 * m * n;
                c = n * n + m * m;

                k = 1;
                while (k * (a + b + c) <= lim)
                {
                    if (check(k * a, k * b, k * c))
                        ++count;
                    ++k;
                }
            }

    std::cout << count << '\n';
    // Brute force, runs in ~ 900ms
}
