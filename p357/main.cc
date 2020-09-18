#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

vector<size_t> primeSieve(size_t upperLim)
{
    size_t next = 3;
    vector<size_t> primes = {2};

    while (next <= upperLim)
    {
        for (auto prime : primes)
        {
            if (next % prime == 0)
                break;

            if (prime > sqrt(next))
            {
                primes.push_back(next);
                break;
            }
        }
        next += 2;
    }
    return primes;
}

bool isPrime(size_t num, vector<size_t> const &primes)
{
    if (num < 2)
        return false;
    
    size_t idx = 0;
    while (primes[idx] <= sqrt(num))
    {
        if (num % primes[idx] == 0)
            return false;        
        
        ++idx;
    }

    return true;
}

vector<size_t> primeFactors(size_t num, vector<size_t> const &primes)
{
    vector<size_t> factors;
    size_t prime, idx = 0;

    while (((num >> 1) << 1) == num)
    {
        factors.push_back(2);
        num >>= 1;
    }

    while (primes[idx] <= sqrt(num))
    {
        prime = primes[idx];
        
        while (num % prime == 0)
        {
            factors.push_back(prime);
            num /= prime;
        }
        
        ++idx;
    }
  
    if (num > 2)
        factors.push_back(num);
    
    return factors;
}

set<size_t> factors(size_t number, vector<size_t> const &primes)
{
    vector<size_t> primefacs(primeFactors(number, primes));
    
    size_t num;
    set<size_t> factors = {1};
    
    for (int comb = 1; comb != (1 << primefacs.size()); ++comb)
    {
        num = 1;

        for (size_t idx = 0; idx != primefacs.size(); ++idx)
            if (comb & 1 << idx)
                num *= primefacs[idx];

        factors.insert(num);
    }

    return factors;
}

bool condition(size_t num, vector<size_t> const &primes)
{
    for (size_t factor : factors(num, primes))
        if (not isPrime(factor + num / factor, primes))
            return false;
    
    return true;
}

int main()
{
    size_t const lim = 100'000'000;
    vector<size_t> const primes = primeSieve(2 * sqrt(lim));

    size_t count = 0;
    for (size_t num = 1; num <= lim; ++num) // Not exceeding.
        if (isPrime(1 + num, primes)) // Optimization: 1 is always a factor.
            if (condition(num, primes))
                count += num;
    
    cout << count << '\n';
}

// 7m9s.
