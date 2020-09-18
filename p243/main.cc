#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isPrime(size_t num)
{
    if (num > 2)
    {
        if (num % 2 == 0)
            return false;
       
        for (size_t idx = 3; idx < floor(sqrt(num)) + 1; idx += 2)
            if (num % idx == 0)
                return false;

        return true;
    }
    
    if (num == 2)
        return true;

    return false;
}

vector<size_t> genPrimes(size_t upperlim)
{
    vector<size_t> primes;
    
    for (size_t idx = 3; idx != upperlim + 1; ++idx)
        if (isPrime(idx))
            primes.push_back(idx);
    
    return primes;
}

size_t totient(size_t num, vector<size_t> const &primes)
{
    vector<size_t> factors;
    size_t totient = num;
    size_t prime;

    if (((num >> 1) << 1) == num)           // If num % 2 == 0,
    {
        totient -= totient / 2;
        
        while (((num >> 1) << 1) == num)    // If num % 2 == 0,
            num >>= 1;                      // divide num by 2.
    }
    
    size_t idx = 0;
    while (primes[idx] <= sqrt(num))
    {
        prime = primes[idx];

        if (num % prime == 0)
        {
            totient -= totient / prime;
            
            while (num % prime == 0)
                num /= prime;
        }
        ++idx;
    }

    if (num > 2)  
        totient -= totient / num;

    return totient;
}

int main()
{
    size_t limit = 10'000'000'000;

    vector<size_t> primes = genPrimes(3*ceil(sqrt(limit)));
    cout << "generated primelist of size " << primes.size() << '\n';

    for (size_t d = 2; d != limit; ++d)
        if (totient(d, primes) / (d - 1.0) < 15499.0/94744.0)
        {
            cout << d << '\n';
            break;
        }
}

 // 892371480 63m31s on i5 7600k one core.
