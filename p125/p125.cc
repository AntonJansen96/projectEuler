#include "euler/euler.h"
#include <iostream>
#include <set>

int main()
{
    int const lim = 100'000'000;
    
    std::set<int> ConsecutiveSquareSums; // Generate all possible ...
    for (int a = 1; a <= std::sqrt(lim); ++a)
    {
        int x = a * a;
        for (int b = a + 1; b <= std::sqrt(lim); ++b)
            if (x <= lim)
            {
                if (x != a * a) // we need at least two terms
                    ConsecutiveSquareSums.insert(x);
                
                x += b * b; // add the next term
            }
    }

    size_t total = 0;
    for (int const element : ConsecutiveSquareSums)
        if (euler::isPalindrome(element))
            total += element;
    
    std::cout << total << '\n';
}
