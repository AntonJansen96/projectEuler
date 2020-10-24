#include "euler/euler.h"
#include <iostream>
#include <set>
#include <algorithm>

int main()
{
    euler::Primetools p;
    
    // Array containing all 1 to 9 pandigital numbers.
    auto const pandigList = euler::genPandigital(1, 9);

    std::set<std::vector<size_t>> setList; // Us this to count distinct sets.

    for (auto const pandig : pandigList)
    {
        euler::NumberSplit split(pandig);

        while (not split.done())
        {
            auto set = split.yieldNext();

            bool good = true; // Check if all numbers in the set are prime
            for (auto const number : set)
                if (not p.isPrime(number))
                {
                    good = false;
                    break;
                }
            
            if (good) // If all number in set are prime
            {
                std::sort(set.begin(), set.end());
                setList.insert(set);
            }
        }
    }

    std::cout << setList.size() << '\n';
}
