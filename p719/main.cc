// #include "euler/euler.h"
// #include <iostream>

// bool check(size_t num, size_t target)
// {
//     if (num < target)
//         return false;
    
//     int numdig = euler::numDigits(num);
    
//     for (int i = 1; i != numdig; ++i)
//     {
//         size_t a = euler::firstNdigits(num, i);
//         size_t b = euler::lastNdigits(num, numdig - i);

//         if (a + b == target)
//             return true;

//         if (check(b, target - a) and (target > a))
//             return true;
//     }

//     return false;
// }

// int main()
// {
//     size_t sum = 0;

//     for (size_t num = 1; num <= 1'000'000; ++num)
//         if (check(num * num, num))
//             sum += num * num;
    
//     std::cout << sum << '\n';
// }

#include <iostream>

bool check(size_t num, size_t target)
{
    if (num < target)   // Not relevant to actual algorithm.
        return false;   // Just a (huge) speedup as this will never be true.

    if (num == target)
        return true;

    size_t factor = 10;
    while (factor < num)
    {
        size_t a = num % factor;        // Core problem is how to find a 
        size_t b = num / factor;        // and b in a smart/fast way.
        
        if (check(b, target - a) and (a <= target))
            return true;    // If we recursively find a situation where true 
                            // AND target did not became negative, we are done.
        factor *= 10;
    }

    return false;
}

int main()
{
    size_t sum = 0;

    for (size_t num = 2; num <= 1'000'000; ++num)
        if (check(num * num, num))
            sum += num * num;
    
    std::cout << sum << '\n';
}
