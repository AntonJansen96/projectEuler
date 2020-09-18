#include <iostream>
#include <cmath>

int main()
{
    int    target = 2'000'000;
    size_t diff   = target;
    size_t lim    = 100;

    size_t storeM;
    size_t storeN;

    for (size_t M = 1; M != lim; ++M)
        for (size_t N = M; N != lim; ++N)
        {
            int triangles = M * (M + 1) * N * (N + 1) / 4;
            
            if (abs(target - triangles) < diff)
            {
                diff = abs(target - triangles);
                storeM = M;
                storeN = N;
            }
        }
    
    std::cout << storeM * storeN << '\n';
}
