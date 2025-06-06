// We're interested in values of n for which this equation has (exactly one)
// solution: x^2 - y^2 - z^2 = n.

// The fact that they’re consecutive terms in an arithmetic expression:

// x = y + d
// z = y - d

// Substituting gives:

// (y+d)^2 - y^2 - (y-d)^2 = n
// n = y(4d-y)

// Now, n, y, and d are all integers and they're all positive > 0.
// This means that d must be, at minimum, d = y/4 + 1/4 for n to be positive.
// However, d must be an integer, so we cannot add 1/4 but must add 1, giving
// the condition that d is, at minimum for a given y, d = y / 4 + 1.

// Now, we loop over all 0 < y < lim, and d in the range [y / 4 + 1, lim).
// We also must keep in the mind the condition that z > 0, so z = y - d
// must be satisfied.

#include <iostream>
#include <vector>

int main()
{
    size_t const lim = 50'000'000;
    std::vector<size_t> solutions(lim);
    size_t n;

    for (size_t y = 1; y != lim; ++y)
    {
        for (size_t d = y / 4 + 1; d != lim; ++d)
        {
            if (!(y - d > 0))           // z = y - d must be a positive int.
                break;                  // We can break here instead of
                                        // continue because d keeps growing.
            n = y * (4 * d - y);

            if (n > lim)                // Limits n to n < lim. Also speedup.
                break;

            if (n > 0)                  // Limits n to n > 0.
                ++solutions[n];
        }
    }

    size_t count = 0;                   // Count #elements in the solutions 
    for (auto val : solutions)          // vector which have value 1, i.e.
        if (val == 1)                   // one unique solution.
            ++count;

    std::cout << count << std::endl;    // 2544559 ~ 1s on M1.
}
