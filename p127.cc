#include "euler/euler.h"
#include "easy/easy.h"
#include <iostream>
#include <omp.h>
#include <atomic>

int main()
{
    euler::Primetools p;

    size_t lim = 120'000;
    std::atomic<size_t> abchits{0}, abchitsum{0};
    for (size_t a = 1; a != lim; ++a)
    {
        std::cout << a << '\n';
        for (size_t b = a + 1; b != lim; ++b)
        {
            size_t c = a + b;

            if (c >= 120'000)
                break;

	    if (euler::isCoprime(a, b) and euler::isCoprime(a, c))
                if (easy::prod(p.factorPrimeSingle(a*b*c)) < c)
                {
                    abchitsum += c;
                    ++abchits;
                }
        }
    }
    
    std::cout << abchits << ", " << abchitsum << '\n';
}
