#include "stopwatch/stopwatch.h"
#include "euler/euler.h"
#include "easy/easy.h"
#include <iostream>
#include <omp.h>
#include <atomic>

Stopwatch timer("prime generation");
euler::Primetools p{1'000'000'000'000'000};

size_t nextPrime(size_t prime)
{
    size_t num = prime + 2;
    while (true)
    {
        if (p.isPrime(num))
            return num;

        num += 2;
    }
}

size_t check(size_t n)
{
    if (not p.isPrime(n * n + 1))
        return false;
    
    if 
    (
        nextPrime(n * n + 1)  == n * n + 3  and
        nextPrime(n * n + 3)  == n * n + 7  and
        nextPrime(n * n + 7)  == n * n + 9  and
        nextPrime(n * n + 9)  == n * n + 13 and
        nextPrime(n * n + 13) == n * n + 27
    )
        return true;
    
    return false;
}

int main()
{
    timer.time();
    Stopwatch timer2("main");
    std::atomic<size_t> total{0};

    #pragma omp parallel for
    for (size_t n = 10; n < 1'000'000; ++n)
        if (check(n))
            total += n;

    timer2.time();
    std::cout << total << '\n';
}

    // Assert example
    // int num = 10;
    // std::cout   << num*num + 1 << ", "
    //             << num*num + 3 << ", "
    //             << num*num + 7 << ", "
    //             << num*num + 9 << ", "
    //             << num*num + 13 << ", "
    //             << num*num + 27 << '\n';