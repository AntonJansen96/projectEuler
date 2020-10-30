#include "euler/euler.h"
#include <iostream>
#include <omp.h>
#include <atomic>

euler::Primetools p;

size_t check(size_t n)
{
    if (
            p.miller_rabin(n * n + 1)  and
            p.miller_rabin(n * n + 3)  and
        not p.miller_rabin(n * n + 5)  and
            p.miller_rabin(n * n + 7)  and
            p.miller_rabin(n * n + 9)  and
        not p.miller_rabin(n * n + 11) and
            p.miller_rabin(n * n + 13) and
        not p.miller_rabin(n * n + 15) and
        not p.miller_rabin(n * n + 17) and
        not p.miller_rabin(n * n + 19) and
        not p.miller_rabin(n * n + 21) and
        not p.miller_rabin(n * n + 23) and
        not p.miller_rabin(n * n + 25) and
            p.miller_rabin(n * n + 27)
    )
        return true;
    
    return false;
}

int main()
{
    std::atomic<size_t> total{0};

    #pragma omp parallel for
    for (size_t n = 10; n < 150'000'000; n += 1)
        if (check(n))
        {
            std::cout << n << '\n';
            total += n;
        }

    std::cout << total << '\n';
}
