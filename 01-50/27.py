from math import sqrt; from itertools import count, islice

def isprime(n):
    return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

p = -1

for a in xrange(-999,1000):
	for b in xrange(-1000,1001):
		
		n      = 0
		c      = True

		while c:
			number = n**2 + a*n + b
			if isprime(number) is True:
				n = n + 1
			else:
				if n > p:
					large_a = a
					large_b = b
					p = n
					print("%s (%s,%s) (%s primes)" % (large_a*large_b, large_a, large_b, p))
				c = False

#Solved

#include <eulerlib.h>
#include <iostream>

# using namespace std;

# int main()
# {
#     // Generate primelist (largest a * b ~ 10E6 and sqrt(10E6) = 10E3).
#     vector<size_t> const primes = euler::primeSieve(1000);
    
#     int a_mem, b_mem, n, max = 0;

#     for (int a = -999; a < 1000; ++a)
#         for (int b = -1000; b <= 1000; ++b)
#         {
#             n = 0;
#             while (euler::isPrime(n*n + a*n + b, primes))
#                 ++n;
                
#             if (n > max)
#                 a_mem = a, b_mem = b, max = n;
#         }
    
#     cout << a_mem * b_mem << '\n';
# }
