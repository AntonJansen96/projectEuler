#include <iostream>
#include <atomic>
#include <omp.h>

size_t pisano(size_t n)
{
    size_t a = 0; 
    size_t b = 1;
    size_t c = a + b;

    for (size_t idx = 0; idx < n * n; ++idx)
    {
        c = (a + b) % n;
        a = b;
        b = c;
        if (a == 0 && b == 1)
            return idx + 1;
        
        // This is a massive optimization for our particular problem.
        if (idx + 1 > 120) 
            return 0;
    }
    return 0;
}

int main() 
{
    // Assert examples.
    std::cout << std::boolalpha << (pisano(3) == 8) << '\n';
    std::cout << std::boolalpha << (pisano(19) == 18) << '\n';
    std::cout << std::boolalpha << (pisano(38) == 18) << '\n';
    std::cout << std::boolalpha << (pisano(76) == 18) << '\n';

    std::atomic<size_t> total = 0;
    
    #pragma omp parallel for
    for (size_t num = 1; num < 1'000'000'000; ++num)
    {
        if (pisano(num) == 120)
            total += num;
    }

    std::cout << total << '\n';
}

// 44511058204 ~ 1:30s on M1.
