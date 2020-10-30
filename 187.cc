#include "easy/easy.h"
#include "euler/euler.h"
#include <iostream>
#include <omp.h>
#include <atomic>

int main()
{
    int const lim = 100'000'000;

    euler::Primetools p(lim);
    
    std::atomic<size_t> total{0};
    
    #pragma omp parallel for
    for (int n = 4; n < lim; ++n)
        if (p.factorPrime(n).size() == 2)
            ++total;
    
    std::cout << total << '\n';
}