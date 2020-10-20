#include "fastmath/fastmath.h"
#include "euler/euler.h"
#include <iostream>
#include <vector>

euler::Primetools p;
static std::vector<size_t> const primes = p.sieve(1'000'000);

size_t compute(size_t n)
{
    size_t a = fastMath::pow_mod(primes[n-1] - 1, n, primes[n-1] * primes[n-1]);
    size_t b = fastMath::pow_mod(primes[n-1] + 1, n, primes[n-1] * primes[n-1]);

    return a + b;
}

int main()
{
    int num = 7037;
    while (true)
    {
        if (compute(num) > 10'000'000'000)
        {
            std::cout << num << ", " << compute(num) << '\n';
            break;
        }

        num += 2;
    }
}

// Solved, although I think there is a bug in pow_mod function as it 
// gives wrong values for even number inputs.
