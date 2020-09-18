#include <iostream>
#include <cmath>

int main()
{
    int Nsolutions = 0;
    int x = 1;

    while(Nsolutions <= 1'000'000)
    {
        for (int y = 1; y <= x; ++y)
            for (int z = 1; z <= y; ++z)
            {
                int minPathSquared = (x * x) + (y + z) * (y + z);
                int minPath = sqrt(minPathSquared);

                if(minPath * minPath == minPathSquared)
                    ++Nsolutions;
            }
        ++x;
    }

    std::cout << x - 1 << '\n';
}

// double shortestPath(int x, int y, int z)
// {
//     return sqrt((x * x) + (y + z) * (y + z));  // l_min = sqrt(x^2 + (y + z)^2)
// }

// bool isint(double num)
// {
//     return (static_cast<int>(num) == num);
// }

// int main()
// {
//     int x = 1;
//     int Nsolutions = 0;

//     while(Nsolutions <= 1'000'000)
//     {
//         for (int y = 1; y <= x; ++y)
//             for (int z = 1; z <= y; ++z)
//                 if(isint(shortestPath(x, y, z)))
//                     ++Nsolutions;
        
//         ++x;
//     }

//     std::cout << x - 1 << '\n';
// }