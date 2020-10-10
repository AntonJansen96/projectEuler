#include "euler/euler.h"
#include <iostream>
#include <vector>
#include <atomic>
#include <omp.h>

int main()
{
    size_t const uplim = 40'000'000;

    euler::Primetools p{uplim};

    std::vector<size_t> totientList(uplim, 0);

    #pragma omp parallel for
    for (size_t num = 2; num < uplim; ++num)
        totientList[num] = p.totient(num);
    
    std::atomic<size_t> total; total = 0;
    
    #pragma omp parallel for
    for (size_t num = 3; num < uplim; num += 2)
        if (p.isPrime(num))
        {
            size_t next = num, count = 1;
            
            while (next != 1)
            {
                next = totientList[next];
                ++count;

                if (count == 25)
                {
                    if (next == 1)
                        total += num;

                    break;
                }
            }
        }

    std::cout << total << '\n';
}

// Solved (1677366278943) runs in ~5.2 s on amd ryzen 8 core.
