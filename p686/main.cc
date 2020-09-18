#include <iostream>
#include <cmath>

size_t firstNdigits(size_t base, size_t exp, size_t N)
{
    double num = exp * log10(base);
    num -= floor(num);
    num = pow(10, num);
    
    return static_cast<size_t>(floor(pow(10, N - 1) * num));
}

int main()
{
    size_t count = 0;
    size_t exp = 0;
    
    while (count != 678910)
    {
        ++exp;
        
        if (firstNdigits(2, exp, 3) == 123)
            ++count;
    }

    std::cout << exp << '\n';
}