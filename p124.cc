#include "euler/euler.h"
#include "easy/easy.h"
#include <iostream>
#include <map>

int main()
{
    euler::Primetools p;
    std::multimap<int, int> dict;

    for (int n = 1; n <= 100'000; ++n)
        dict.insert({easy::prod(p.factorPrimeSingle(n)), n});

    std::cout << std::next(dict.begin(), 10'000 - 1)->second << '\n';
}
