#include "stopwatch/stopwatch.h"
#include "easy/easy.h"
#include "euler/euler.h"
#include <math.h>

static size_t const xx  = 1'000'000'007;

template <class T>
T mul_mod(T a, T b, T m) { 
    if (m == 0) return a * b;

    T r = T();

    while (a > 0) {
        if (a & 1)
            if ((r += b) > m) r %= m;
        a >>= 1;
        if ((b <<= 1) > m) b %= m;
    }
    return r;
}

template <class T>
T pow_mod(T a, T n, T m) {
    T r = 1;

    while (n > 0) {
        if (n & 1)
            r = mul_mod(r, a, m);
        a = mul_mod(a, a, m);
        n >>= 1;
    }
    return r;
}

size_t s(int n)
{
    int num = 1;
    while (true)
    {
        if (euler::sumDigits(num) == n)
            return num;
        
        ++num;
    }
}

size_t Sold(size_t k)
{
    size_t total = 0;
    for (size_t n = 1; n <= k; ++n)
        total += s(n);
    
    return total;
}

size_t S(size_t k, std::vector<size_t> const &smallestList)
{
    size_t total = 0;
    for (size_t idx = 0; idx <= k; ++idx)
    {
        total += smallestList[idx];
        total %= xx;
    }
    
    return total;
}

int main()
{
    std::vector<size_t> fibs = {1};
    size_t idx = 1, next = 1;

    while(fibs.size() != 90)
    {
        fibs.push_back(next % 1'000'000'007);
        next = fibs[idx - 1] + fibs[idx];
        ++idx;
    }
    fibs.erase(fibs.begin());

    easy::print(fibs);
    std::cout << fibs.size() << '\n';
   
    Stopwatch timer("build array");

    size_t const val = 10; size_t ID = 0;
    std::vector<size_t> smallestList((120'000'000+1)*9, 0);
    for (size_t j = 0; j <= 120'000'000; ++j)
        for (size_t i = 1; i <= 9; ++i)
        {
            smallestList[ID] = i * pow_mod(val, j, xx) - 1;
            ++ID;
            // smallestList.push_back(i * pow_mod(val, j, xx) - 1);
        }

    timer.time();

    // easy::print(smallestList);
    std::cout << smallestList.size() << '\n';

    // std::cout << S(20, smallestList) << '\n';
    // std::cout << Sold(20) << '\n';

    size_t target = 0;
    for (auto fib : fibs)
    {
        target += S(fib, smallestList);
        target %= xx;
        // test += Sold(fib);
        // test %= xx;
    }
    
    std::cout << target << '\n';
    // std::cout << test << '\n';
}
