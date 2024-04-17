#include <iostream>
#include "euler/euler.h"

// Returns the smallest value k for which R(k) is divisible by n.
int A(int n)
{
    int m = 1;
    int k = 1;
    while (m != 0)
    {
        m = (m * 10 + 1) % n;
        k += 1;
    }
    return k;
}

int main()
{
    int num = 1'000'000; // Start high to save time.
    while (true)
    {
        if (euler::gcd(num, 10) == 1 and A(num) > 1'000'000)
        {
            std::cout << num << '\n';
            break;
        }
        num += 1;
    }
}
