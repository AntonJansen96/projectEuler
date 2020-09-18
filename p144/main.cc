#include <iostream>
#include <cmath>

int main()
{
    double x0 = 0;          // First coordinate.
    double y0 = 10.1;
    double x1 = 1.4;        // Second coordinate.
    double y1 = -9.6;
    int reflections = 1;    // #reflections.

    while (true)
    {
        double m0 = (y1 - y0) / (x1  - x0);             // Compute m0.
        
        double m1 = -4 * x1 / y1;                       // Compute m1.
        
        double tan_a = (m0 - m1) / (1 + m0 * m1);       // Compute m2.
        double m2 = (m1 - tan_a) / (1 + tan_a * m1);

        double c = m2;                                  // Compute c, d in 
        double d = y1 - c * x1;                         // y = cx + d.

        // Compute intersections.
        double x_a =  (2 * sqrt(25 * c * c - d * d + 100) - c * d) / (c * c + 4);
        double x_b = -(2 * sqrt(25 * c * c - d * d + 100) + c * d) / (c * c + 4);

        // From these, choose values with x2 farthest from x1.
        double x2 = (std::abs(x_a - x1) > std::abs(x_b - x1)) ? x_a : x_b;
        double y2 = c * x2 + d;

        if ((x2 >= -0.01) && (x2 <= 0.01) && (y2 > 0))  // Break if satisfied.
            break;

        x0 = x1; x1 = x2;
        y0 = y1; y1 = y2;

        ++reflections;
    }
    std::cout << reflections << '\n';
}


// #include <iostream>
// #include <cmath>
// #include <utility>

// using namespace std;

// typedef pair<double, double> coord;

// coord compute(coord xn, coord xn_min_1)
// {
//     // COMPUTE m0
//     double m0 = (xn.second - xn_min_1.second) / (xn.first  - xn_min_1.first);

//     // COMPUTE m1 (using slope equation)
//     double m1 = -4 * xn.first / xn.second;
    
//     // COMPUTE m2
//     double tan_a = (m0 - m1) / (1 + m0 * m1);
//     double m2 = (m1 - tan_a) / (1 + tan_a * m1);

//     // COMPUTE c, d IN (y = cx + d);
//     double c = m2;
//     double d = xn.second - c * xn.first;

//     // COMPUTE INTERSECTS
//     double x1 =  (2 * sqrt(25 * c * c - d * d + 100) - c * d) / (c * c + 4);
//     double x2 = -(2 * sqrt(25 * c * c - d * d + 100) + c * d) / (c * c + 4);

//     // CHOOSE VALUE WITH X FURTHEST FROM x0
//     double x = (abs(x1 - xn.first) > abs(x2 - xn.first)) ? x1 : x2;
//     double y = c * x + d;

//     return make_pair(x, y);
// }

// int main()
// {
//     coord c1 = make_pair(0, 10.1);
//     coord c2 = make_pair(1.4, -9.6);

//     size_t reflections = 1;

//     while (true)
//     {
//         coord c3 = compute(c2, c1);
        
//         c1 = c2;
//         c2 = c3;

//         if ((c2.first >= -0.01) && (c2.first <= 0.01) && (c2.second > 0))
//             break;

//         ++reflections;
//     }

//     cout << reflections << '\n';
// }
