#include <iostream>
#include <vector>
#include "euler/euler.h"

size_t reverseNum(size_t num)
{
    size_t invnum = 0;
    while (num)
    {
        invnum = invnum * 10 + (num % 10);
        num /= 10;
    }
    return invnum;
}

bool binarySearch(const std::vector<size_t> &array, size_t target)
{
    size_t left = 0;
    size_t right = array.size() - 1;

    while (left <= right)
    {
        size_t mid = left + (right - left) / 2;

        if (array[mid] == target)       // Found the target. 
            return true; 
        
        else if (array[mid] < target)   // Search in the right half.
            left = mid + 1; 
        
        else                            // Search in the left half
            right = mid - 1; 
    }

    return false;                       // Target not found.
}

int main()
{
    euler::Primetools p;
    std::vector<size_t> primesqarray;

    for (auto prime : p.sieve(40'000'000))
        primesqarray.push_back(prime * prime);

    size_t solution = 0;
    size_t count = 0;
    
    for (auto primesq : primesqarray)
    {
        auto reversed = reverseNum(primesq);
        if (not (primesq == reversed) and binarySearch(primesqarray, reversed))
        {
            solution += primesq;
            ++count;
            
            if (count == 50)
            {
                std::cout << "sum is " << solution << '\n';
                break;
            }  
        }
    }
}

// Project Euler problem 808, runs in roughly 8s.
