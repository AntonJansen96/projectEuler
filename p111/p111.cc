#include "euler/euler.h"
#include <iostream>
#include <atomic>
#include <omp.h>

static euler::Primetools p{10'000'000'000};

static const std::vector<size_t> power = 
{
    1, 10, 100, 1'000, 10'000, 100'000, 1'000'000, 10'000'000, 100'000'000,
    1'000'000'000, 10'000'000'000, 100'000'000'000, 1'000'000'000'000,
    10'000'000'000'000, 100'000'000'000'000, 1'000'000'000'000'000,
    10'000'000'000'000'000, 100'000'000'000'000'000, 
    1'000'000'000'000'000'000
};    

size_t S(size_t n)
{
    std::atomic<size_t> largest0{0}, largest1{0}, largest2{0}, largest3{0},
                        largest4{0}, largest5{0}, largest6{0}, largest7{0},
                        largest8{0}, largest9{0};

    std::atomic<size_t> primeSum0{0}, primeSum1{0}, primeSum2{0}, primeSum3{0},
                        primeSum4{0}, primeSum5{0}, primeSum6{0}, primeSum7{0},
                        primeSum8{0}, primeSum9{0};

    #pragma omp parallel for
    for (size_t num = power[n-1] + 1; num < power[n]; num += 2)
    {
        if (p.isPrime(num))
        {
            size_t count0 = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0,
                   count5 = 0, count6 = 0, count7 = 0, count8 = 0, count9 = 0;
            
            size_t temp = num;
            while (temp)
            {
                switch(temp % 10)
                {
                    case 0: ++count0; break;
                    case 1: ++count1; break;
                    case 2: ++count2; break;
                    case 3: ++count3; break;
                    case 4: ++count4; break;
                    case 5: ++count5; break;
                    case 6: ++count6; break;
                    case 7: ++count7; break;
                    case 8: ++count8; break;
                    case 9: ++count9; break;
                }
                
                temp /= 10;
            }
            
            if (count0 == largest0)
                primeSum0 += num;

            if (count1 == largest1)
                primeSum1 += num;

            if (count2 == largest2)
                primeSum2 += num;

            if (count3 == largest3)
                primeSum3 += num;

            if (count4 == largest4)
                primeSum4 += num;

            if (count5 == largest5)
                primeSum5 += num;

            if (count6 == largest6)
                primeSum6 += num;

            if (count7 == largest7)
                primeSum7 += num;

            if (count8 == largest8)
                primeSum8 += num;

            if (count9 == largest9)
                primeSum9 += num;

            if (count0 > largest0)
            {
                largest0 = count0;
                primeSum0 = num;
            }

            if (count0 > largest0)
            {
                largest0 = count0;
                primeSum0 = num;
            }

            if (count1 > largest1)
            {
                largest1 = count1;
                primeSum1 = num;
            }
            
            if (count2 > largest2)
            {
                largest2 = count2;
                primeSum2 = num;
            }
            
            if (count3 > largest3)
            {
                largest3 = count3;
                primeSum3 = num;
            }
            
            if (count4 > largest4)
            {
                largest4 = count4;
                primeSum4 = num;
            }
            
            if (count5 > largest5)
            {
                largest5 = count5;
                primeSum5 = num;
            }

            if (count6 > largest6)
            {
                largest6 = count6;
                primeSum6 = num;
            }

            if (count7 > largest7)
            {
                largest7 = count7;
                primeSum7 = num;
            }

            if (count8 > largest8)
            {
                largest8 = count8;
                primeSum8 = num;
            }

            if (count9 > largest9)
            {
                largest9 = count9;
                primeSum9 = num;
            }            
        }
    }

    std::cout << 0 << ", " << primeSum0 << '\n';
    std::cout << 1 << ", " << primeSum1 << '\n';
    std::cout << 2 << ", " << primeSum2 << '\n';
    std::cout << 3 << ", " << primeSum3 << '\n';
    std::cout << 4 << ", " << primeSum4 << '\n';
    std::cout << 5 << ", " << primeSum5 << '\n';
    std::cout << 6 << ", " << primeSum6 << '\n';
    std::cout << 7 << ", " << primeSum7 << '\n';
    std::cout << 8 << ", " << primeSum8 << '\n';
    std::cout << 9 << ", " << primeSum9 << '\n';

    return primeSum0 + primeSum1 + primeSum2 + primeSum3 + primeSum4 +
           primeSum5 + primeSum6 + primeSum7 + primeSum8 + primeSum9;
}

int main()
{
    std::cout << S(10) << '\n';
}
