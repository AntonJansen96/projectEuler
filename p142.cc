#include "euler/euler.h"
#include <iostream>

int main()
{
    size_t const lim = 1'000'000;
    
    for (size_t z = 1; z < lim; ++z)
        for (size_t y = z + 1; y < lim; ++y)
            if (euler::isSquare(y+z) and euler::isSquare(y-z))
                for (size_t x = y + 1; x < lim; ++x)
                    if
                    (
                        euler::isSquare(x+y) and 
                        euler::isSquare(x-y) and 
                        euler::isSquare(x+z) and 
                        euler::isSquare(x-z)
                    )
                    {
                        std::cout << x + y + z << '\n';
                        std::terminate();
                    }
}
