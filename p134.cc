#include "euler/euler.h"
#include <iostream>
#include <atomic>
#include <omp.h>

size_t computeS(size_t p1, size_t p2)
{
    size_t len = euler::numDigits(p1);

    size_t num = 2 * p2;
    while (true)
    {
        if (euler::lastNdigits(num, len) == p1)
            return num;
        
        num += p2;
    }
}

int main()
{
    std::cout << computeS(19, 23) << '\n';  // Assert example

    auto const primes = euler::Primetools().sieve(1'000'004);
                                            // largest is 1'000'003
    std::atomic<size_t> total{0};
    
    #pragma omp parallel for
    for (size_t idx = 2; idx < primes.size() - 1; ++idx)
        total += computeS(primes[idx], primes[idx + 1]);
    
    std::cout << total << '\n';
}

// Solved ~ 1m 18613426663617118
