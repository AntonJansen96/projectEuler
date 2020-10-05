#include "stopwatch/stopwatch.h"
#include "euler/euler.h"
#include "easy/easy.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

typedef std::set<std::vector<size_t>> matrix;

static euler::Primetools p; // Intialize our Primetools object.

// This function generates a vector with factors for each index for fast lookup.
std::vector<std::vector<size_t>> genFactorList(size_t uplim)
{
    std::vector<std::vector<size_t>> FactorList = {{1}, {1}, {1}};
    
    for (size_t num = 3; num <= uplim; ++num)
    {
        auto factors = p.factorAll(num);
        std::sort(factors.begin(), factors.end());  // Sort
        
        factors.erase(factors.begin()); // Remove trivial factor 1
        factors.pop_back();             // Remove trivial factor itself        

        FactorList.push_back(factors);
    }

    return FactorList;
}

auto const FactorList{genFactorList(25000)};

// This function generates all combinations for a given number.
std::vector<std::vector<size_t>> test(std::vector<size_t> const &someSet)
{
    std::vector<std::vector<size_t>> tobeReturned;
    
    // Divide someSet in prime and composite numbers:
    std::vector<size_t> primePart, compositePart;
    for (size_t num : someSet)
    {
        if (p.isPrime(num))
            primePart.push_back(num);
        else
            compositePart.push_back(num);
    }

    if (not compositePart.empty())
    {
        for (size_t factor : FactorList[compositePart[0]])
        {
            std::vector<size_t> someNewSet = primePart;
            
            someNewSet.push_back(factor);
            someNewSet.push_back(compositePart[0] / factor);

            // Add the other composite parts (if any)
            for (size_t idx = 1; idx < compositePart.size(); ++idx)
                someNewSet.push_back(compositePart[idx]);

            // Do not sort because then we lose some sets of factors!.
            // std::sort(someNewSet.begin(), someNewSet.end());
            tobeReturned.push_back(someNewSet);
        }
    }

    return tobeReturned;
}

void matrixPrint(matrix const &input)
{
    for (auto const &element : input)
        easy::print(element);
}

matrix generate(size_t num)
{
    matrix total = {{num}};

    bool condition = true;
    while (condition)
    {
        for (auto set : total)
        {
            auto nieuw = test(set);
            
            if (nieuw.empty())
            {
                condition = false;
                break;
            }

            for (std::vector<size_t> xxx : nieuw)
                total.insert(xxx);
        }
    }

    return total;
}

int main()
{   
    Stopwatch timer("preparatory stuff");
    // Store all the sets for a specific number for faster lookup.
    Stopwatch timer3("memo");
    
    std::vector<matrix> memo;
    
    for (size_t num = 2; num <= 25000; ++num)
        memo.push_back(generate(num));

    timer3.time();

    Stopwatch timer4("memo1 and memo2");

    // Optional speedup
    std::vector<std::vector<size_t>> memo1, memo2;
    for (auto matrix : memo)
    {
        std::vector<size_t> lengths, sums;
        for (auto set : matrix)
        {
            lengths.push_back(set.size());
            sums.push_back(easy::sum(set));
        }

        memo1.push_back(sums);
        memo2.push_back(lengths);
    }

    timer4.time();

    std::set<size_t> minProdSumNums;
    size_t num;
    bool condition;

    timer.time();
    Stopwatch timer2("main loop");

    for (size_t k = 2; k <= 12'000; ++k) // main loop.
    {
        num = k; // speedup
        condition = true;
        
        while (condition)
        {               // loop through all the sets associated with a given num
            for (size_t idx = 0; idx != memo[num-2].size(); ++idx)
                if (memo1[num-2][idx] == num - (k - memo2[num-2][idx]))
                {
                    minProdSumNums.insert(num);
                    condition = false;
                    break;
                }

            ++num;
        }
    }

    timer2.time();

    std::cout << easy::sum(minProdSumNums) << '\n';
}
