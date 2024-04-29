#include "euler/euler.h"
#include <iostream>
#include <atomic>
#include <omp.h>

int main()
{
    euler::Primetools p;
    std::atomic<int> count{0};

    #pragma omp parallel for
    for (size_t n = 2; n <= 50'000'000; ++n)
        if (p.miller_rabin(2*n*n - 1))
            ++count;

    std::cout << count << '\n';
}
