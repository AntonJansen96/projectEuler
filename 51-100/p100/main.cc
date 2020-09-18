#include <iostream>
#include <string>
#include <cmath>

int main()
{
    size_t lim = pow(10, 6);
    
    for (size_t a = 1; a != lim; ++a)
        for (size_t b = 1; b != a; ++b)
            if (2 * a * (a - 1) == (a + b) * (a + b - 1))
            {
                std::cout << a << " blue and " << b << " red, " << "ratio: " 
                          << b / static_cast<double>(a) << '\n';
            }
}
