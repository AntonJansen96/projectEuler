#include "euler/euler.h"
#include "easy/easy.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void assert_example()
{
    size_t smallest = INT64_MAX;
    size_t sum = 0;
    
    for (size_t n = 1; n != 100; ++n)
    {
        size_t value = (1504170715041707 * n) % 4503599627370517;

        if (value < smallest)
        {
            sum += value;
            smallest = value;

            std::cout << std::setprecision(16) << n << ", " << value << ", " << sum << '\n';
        }
    }
    
    std::cout << sum << '\n';
}

void test()
{
    euler::Primetools p;
    auto x = p.factorAll(1504170715041707);
    std::sort(x.begin(), x.end());
    easy::print(x);
}

int main()
{
    assert_example();
    std::cout << euler::math::modinverse(1504170715041707, 4503599627370517) << '\n';
}
