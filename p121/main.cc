#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

size_t factorial(size_t n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

vector<pair<size_t, size_t>> genCombs(size_t turns)
{
    vector<pair<size_t, size_t>> combs;

    for (size_t red = 0; red != floor((turns + 1) / 2.0); ++red)
        combs.push_back(make_pair(turns - red, red));
    
    return combs;
}

size_t computeComb(pair<size_t, size_t> const &comb, size_t turns)
{
    size_t sum = 0;

    string bitmask(comb.second, 1);
    bitmask.resize(turns, 0);

    do
    {
        size_t product = 1;

        for (size_t i = 0; i != turns; ++i)
            if (bitmask[i])
                product *= i + 1;
        
        sum += product;
    } 
        while (prev_permutation(bitmask.begin(), bitmask.end()));
    
    return sum;
}

double pWin(size_t turns)
{
    double sum = 0;

    for (auto comb : genCombs(turns))
        sum += computeComb(comb, turns);

    return sum / factorial(turns + 1);
}

size_t maxPrize(double pWin)
{
    return floor(1.0 / pWin);
}

int main()
{
    size_t turns = 15;
    double P = pWin(turns);

    cout << P << '\n' << maxPrize(P) << '\n';
}
