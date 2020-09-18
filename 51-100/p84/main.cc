#include <iostream>
#include <string>

#include <vector>
#include <algorithm>

#include <random>

using namespace std;

size_t sides = 4;        // Amount of sides of the dice.

///////////////////////////////////////////////////////////////////////////////

size_t dicethrow()
{
    return (rand() % sides + 1) + (rand() % sides + 1);
}

size_t community(size_t pos)
{
    size_t num = rand() % 16;       // 0 to 15.

    switch (num)
    {
        case (0):                   // 1/16 to go to GO (0).
            return 0;
        case (1):                   // 1/16 to got to JAIL (10).
            return 10;
        
        default:                    // 14/16 do nothing.
            return pos;
    }                
}

size_t chance(size_t pos)
{
    size_t num = rand() % 16;       // 0 to 15.

    switch (num)
    {
        case (0):                   // 1/16 to go to GO (0).
            return 0;               
        case (1):                   // 1/16 to got to JAIL (10).
            return 10;
        case (2):                   // 1/16 to go to C1 (11).
            return 11;              
        case (3):                   // 1/16 to go to E3 (24).
            return 24;              
        case (4):                   // 1/16 to go to H2 (39).
            return 39;              
        case (5):                   // 1/16 to got to R1 (5).
            return 5;               
        case (6):                   // 1/16 to go to next railway station (I)
        {
            if (pos < 5)
                return 5;
            if ((5 < pos) && (pos < 15))
                return 15;
            if ((15 < pos) && (pos < 25))
                return 25;
            return 35;
        }
        case (7):                   // 1/16 to go to next railway station (II).
        {
            if (pos < 5)
                return 5;
            if ((5 < pos) && (pos < 15))
                return 15;
            if ((15 < pos) && (pos < 25))
                return 25;
            return 35;
        }        
        case (8):                   // 1/16 to go to next utility company.
        {
            if (pos < 12)
                return 12;
            return 28;
        }
        case (9):                   // 1/16 to go back 3 squares.
            return pos - 3;

        default:                    // 6/16 do nothing.
            return pos;
    }
}

int main()
{
    srand((unsigned) time(NULL));

    vector<size_t> visits(40);

    size_t iterations = 10'000'000;

    size_t pos = 0;     // Starting position.

    for (size_t idx = 0; idx != iterations; ++idx)
    {
        pos += dicethrow();     // Throw dice.
        pos %= 40;              // Apply modulo if we pass start.

        if ((pos == 2) | (pos == 17) | (pos == 33))     // Community chest.
            pos = community(pos);
        
        else if ((pos == 7) | (pos == 22) | (pos == 36))    // Chance.
            pos = chance(pos);
        
        else if (pos == 30)     // Go to jail.
            pos = 10;

        visits[pos] += 1;
    }

    for (size_t idx = 0; idx != 40; ++idx)
        cout << idx << ": " << visits[idx] / static_cast<double>(iterations) << '\n';
}

// Can already tell the answer should be 101524,
// Even though I incorrectly implemented the chance/community chest and did
// not implement the 3 times double go to jail thing.
