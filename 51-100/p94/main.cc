include <iostream>

int main()
{
    int perSum = 0;

    for (int n = 1; n != 22361; ++n)
        for (int m = n + 1; m != 22361; ++m)
        {
            if (m + n < 22361 and abs(n*n + m*m - 4*m*n) <= 1)
                perSum += 2 * (m + n) * (m + n);

            if (m < 15812 and abs(3*n*n - m*m) <= 1)
                perSum += 4 * (m * m);
        }
    
    std::cout << perSum << '\n';
}
