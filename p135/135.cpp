// This problem is for free once I solved P136. See explanation there.

#include <iostream>
#include <vector>

int main()
{
    size_t const lim = 1'000'000;
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
        if (val == 10)                  // one unique solution.
            ++count;

    std::cout << count << std::endl;    // 4989 ~ instant on M1.
}
