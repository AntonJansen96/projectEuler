#include "euler/euler.h"
#include <omp.h>
#include <vector>
#include <atomic>
#include <cmath>
#include <iostream>

size_t largestPrimeFactor(size_t num, std::vector<size_t> const &d_primes)
{
    size_t prime, largest;
    int idx = 1;                        // Start at second prime in d_primes
                                        // (3) because we already checked 2.
    if (((num >> 1) << 1) == num)       // if num % 2 == 0
    {
        largest = 2;                   // Only do this once.
        
        while (((num >> 1) << 1) == num)    // while num % 2 == 0
            num >>= 1;                      // num /= 2
    }
                                        // Only have to check up until root of
    while (d_primes[idx] <= std::sqrt(num))  
    {                                   // num.
        prime = d_primes[idx];          
        
        if (num % prime == 0)
        {
            largest = prime;           // Only do this once.

            while (num % prime == 0)        // While num is divisible by prime
                num /= prime;               // divide.
        }

        ++idx;    
    }
  
    if (num > 2)                        // If at the end we're left with a
        largest = num;                 // number larger than two, it must be
                                        // a prime so add to largest.
    return largest;
}

int main()
{
    auto const primes = euler::Primetools{}.sieve(40'000);

    std::atomic<size_t> count; count = 1;
    
    #pragma omp parallel for
        for (size_t num = 2; num <= 1'000'000'000; ++num)
        {
            if (largestPrimeFactor(num, primes) <= 100)
                ++count;
        }

    std::cout << count << '\n';
}

// solved (2944730) runs in 34m42s on laptop (user 223m26)