#include "euler/euler.h"
#include <iostream>
#include <atomic>
#include <omp.h>

int main()
{
    euler::Primetools p{64'000'000};
    std::atomic<size_t> total{0};

    #pragma omp parallel for
    for (size_t n = 1; n < 64'000'000; ++n)
        if (euler::isSquare(p.divisorSum(n, 2)))
            total += n;
            
    std::cout << total << '\n';
}
