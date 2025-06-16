#include "cpplib/euler.h"
#include "cpplib/pythonlike.h"
#include "cpplib/stopwatch.h"

int main()
{   // 10s.
    euler::uInt const lim = 1'000'000'000'000;

    // Primes less than 100.
    euler::Primetools p;    
    std::vector<euler::uInt> const primes = p.sieve(100);

    // Basis numbers (all combs of [4 primes < 100]).
    // Generate and print all combinations of 4 primes < 100
    std::vector<euler::uInt> array;
    for (const auto &comb : euler::genCombs(primes, 4))
        array.push_back(comb[0] * comb[1] * comb[2] * comb[3]);
    array = pythonlike::sorted(array);

    // Choose numbers below lim (this will be all (redundant) for large lim).
    std::vector<euler::uInt> sel;
    for (const auto num : array)
        if (num < lim)
            sel.push_back(num);

    // MAIN CODE
    size_t count = sel.size();
    stopwatch::ProgressReport progress(sel.size() - 1);

    #pragma omp parallel for schedule(dynamic, 1) reduction(+ : count)
    for (size_t i = 0; i != sel.size(); ++i)
    {
        euler::uInt x = sel[i];
        while (true)
        {
            x += sel[i];
            if (x >= lim)
                break;
            else
                ++count;
        }
        progress.tick();
    }
    progress.join();
    pythonlike::print(count);
}
