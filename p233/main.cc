#include <iostream>
#include <cmath>
#include <vector>
#include <thread>

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

size_t Ntriples(size_t num, vector<size_t> const &primes)
{
    size_t r = 1;
    size_t exp;
    size_t prime;

    while (((num >> 1) << 1) == num)        // If num % 2 == 0,
        num >>= 1;                          // divide num by 2.
    
    size_t idx = 0;
    while (primes[idx] <= sqrt(num))
    {
        prime = primes[idx];
        
        if (num % prime == 0)
        {
            if (prime % 4 == 1)
            {
                exp = 0;
                while (num % prime == 0)
                {
                    ++exp;
                    num /= prime;
                }

                r *= (2 * exp + 1);
            }
            else
            {
                while (num % prime == 0)
                    num /= prime;
            }
        }
        ++idx;
    }

    if ((num > 2) && (num % 4 == 1))
        r *= 3;

    return 4 * r;
}

void compute(size_t &count, size_t lower, size_t upper, vector<size_t> const &primes)
{
    for(size_t N = lower; N != upper; ++N)
        if (Ntriples(N, primes) == 420)
            count += N;
    
    cout << "finished " << lower << " to " << upper << '\n';
}

int main()
{  
    size_t const lim = 10'000'000;
    
    vector<size_t> const primes = primeSieve( 2 * ceil(sqrt(lim)) );
    
    size_t count = 0;
    
    ///////////////////////////////////////////////////////////////////////////
    size_t multiplier = 10;
    size_t min = 3, max = lim;
    
    size_t NCPUthreads = multiplier * thread::hardware_concurrency();
    vector<thread> threads;

    for (double N = 0; N != NCPUthreads; ++N)
    {
        size_t lower = (N == 0) ? min : floor(max * (N / NCPUthreads));
        size_t upper = floor(max * ((N + 1) / NCPUthreads));

        threads.push_back(thread(compute, ref(count), lower, upper, ref(primes)));
    }

    for (auto &thread : threads)
        thread.join();
    ///////////////////////////////////////////////////////////////////////////

    cout << count << '\n';
}

// 10**8  takes 3m11s on z270k
// 10**9  takes 76m15s (26244481306266) on z270k
// 10**9  takes 21m10s (26244481306266) on 4cores (0-35, 35-60, 60-80, 80-10).
// 10**10 takes 8h6m (2709839225627731)
//  3               10'000'000'000      2709839225627731

// 236222675359
