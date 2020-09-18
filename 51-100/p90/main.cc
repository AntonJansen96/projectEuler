#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<set<int>> genDice()
{
    vector<set<int>> diceCombs;
    
    for (int a1 = 0; a1 != 10; ++a1)
        for (int a2 = a1 + 1; a2 != 10; ++a2)
            for (int a3 = a2 + 1; a3 != 10; ++a3)
                for (int a4 = a3 + 1; a4 != 10; ++a4)
                    for (int a5 = a4 + 1; a5 != 10; ++a5)
                        for (int a6 = a5 + 1; a6 != 10; ++a6)
                        {
                            set<int> comb = {a1, a2, a3, a4, a5, a6};

                            if (comb.find(6) != comb.end())
                                comb.insert(9);
                            else if (comb.find(9) != comb.end())
                                comb.insert(6);

                            diceCombs.push_back(comb);
                        }

    return diceCombs;
}

set<int> genNumbers(set<int> const &set1, set<int> const &set2)
{
    set<int> combs;
    
    for (int ii : set1)
        for (int jj : set2)
        {
            combs.insert(10 * ii + jj);
            combs.insert(ii + 10 * jj);
        }
    
    return combs;
}

bool checkSquares(set<int> const &combs)
{   
    for (int square : {1, 4, 9, 16, 25, 36, 49, 64, 81})
        if (combs.find(square) == combs.end())
            return false;
    
    return true;
}

int main()
{
    vector<set<int>> diceCombs = genDice();

    size_t count = 0;

    for (auto ii = diceCombs.begin(); ii != diceCombs.end(); ++ii)
        for (auto jj = ii; jj != diceCombs.end(); ++jj)
            if(checkSquares(genNumbers(*ii, *jj)))
                ++count;

    cout << count << '\n';
}
