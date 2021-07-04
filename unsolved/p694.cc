#include <iostream>
#include "euler/euler.h"

euler::Primetools p;

bool cubefull(long n)
{
    if (n == 1)         // 1 is considered cube-full.
        return true;
    
    for (auto prime : p.factorPrimeSingle(n))
        if (n % (prime * prime * prime) != 0)
            return false;

    return true;
}

long s(long n)
{
    long count = 0;
    
    for (auto divisor : p.factorAll(n))
        if (cubefull(divisor))
            ++count;

    return count;
}

long S(long n)
{
    long sum = 0;
    for (long i = 1; i <= n; ++i)
        sum += s(i);
    
    return sum;
}

void assert_example()
{
    std::cout << 16 << " -> " << S(16) << '\n';
    std::cout << 100 << " -> " << S(100) << '\n';
    std::cout << 10000 << " -> " << S(10000) << '\n';
}

int main()
{
    assert_example();

    for (size_t n = 1; n <= 40; ++n)
        std::cout << S(n) << '\n';
}
