#include <iostream>
#include <vector>

int main()
{
    int const GridSize = 50;

    std::vector<int> coordListX, coordListY;    // Generate a collection of 
                                                // every coordinate in the grid.
    for (int x = 0; x <= GridSize; ++x)
        for (int y = 0; y <= GridSize; ++y)
        {
            coordListX.push_back(x);    // Stores the x values of the coords.
            coordListY.push_back(y);    // Stores the y values of the coords.
        }

    int const x_1 = 0, y_1 = 0;         // First coord is always the origin.
    int x_2, x_3, y_2, y_3, aa, bb, cc, hyp, rest;
    int TriangleCount = 0;

    // Generate all possible combinations of 3 coords, including the origin.
    for (size_t x = 0; x != coordListX.size(); ++x)
    {
        for (size_t y = x; y != coordListY.size(); ++y)
        {
            x_2 = coordListX[x];    // x-value of coordinate 2.
            x_3 = coordListX[y];    // x-value of coordinate 3.
            y_2 = coordListY[x];    // y-value of coordinate 2.
            y_3 = coordListY[y];    // y-value of coordinate 3.

            // If the second and third coordinates are the same, stop.
            if (x_2 == x_3 and y_2 == y_3)
                continue;

            // If the second or third coordinate is also the origin, stop.
            if ((x_2 == x_1 and y_2 == y_1) or (x_3 == x_1 and y_3 == y_1))
                continue;

            // If a^2 + b^2 != c^2 we know it is not a triangle, stop.
            aa = (x_1 - x_2)*(x_1 - x_2) + (y_1 - y_2)*(y_1 - y_2);
            bb = (x_2 - x_3)*(x_2 - x_3) + (y_2 - y_3)*(y_2 - y_3);
            cc = (x_3 - x_1)*(x_3 - x_1) + (y_3 - y_1)*(y_3 - y_1);
            
            if (aa > bb and aa > cc)
            {
                hyp = aa;
                rest = bb + cc;
            }
            else if (bb > aa and bb > cc)
            {
                hyp = bb;
                rest = aa + cc;
            }
            else
            {
                hyp = cc;
                rest = aa + bb;
            }
            
            if (hyp != rest)
                continue;
            
            // What we are left with are triangles, so increase count.
            ++TriangleCount;
        }
    }

    std::cout << TriangleCount << '\n';
}
