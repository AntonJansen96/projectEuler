#include "easy/easy.h"
#include "euler/euler.h"
#include <iostream>
#include <omp.h>
#include <atomic>

int main()
{
    int const lim = 10'000'000;

    euler::Primetools p(lim);
     std::atomic<size_t> total{0};
 
    #pragma omp parallel for
    for (int n = 1; n < lim - 1; ++n)
        if (p.divisorSum(n, 0) == p.divisorSum(n + 1, 0))
            ++total;
    
    std::cout << total << '\n';
}
