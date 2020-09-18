from math import sqrt; from itertools import count, islice

def isprime(n):
	return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

for i in xrange(1000,10000-2*3330):
	if isprime(i) is True and isprime(i+3330) is True and isprime(i+6660) is True:
		print(i,i+3330,i+6660)

#Solved (296962999629)

# #include <eulerlib.h> // My own library.
# #include <iostream>
# #include <vector>
# #include <tuple>
# #include <string>
# #include <algorithm>

# using namespace std;

# int main()
# {
#     auto const primes = euler::sieve(5000);

#     for (size_t num = 1488; num != 10000 - 6660; ++num)
#         if
#         (
#             euler::isPrime(num,        primes) &&
#             euler::isPrime(num + 3330, primes) &&
#             euler::isPrime(num + 6660, primes)
#         )
#         {
#             auto const [str1, str2, str3] = tuple
#             {
#                 to_string(num), 
#                 to_string(num + 3330), 
#                 to_string(num + 6660)
#             };
            
#             if
#             (
#                 is_permutation(str1.begin(), str1.end(), str2.begin()) &&
#                 is_permutation(str2.begin(), str2.end(), str3.begin())
#             )
#             {
#                 cout << num << num + 3330 << num + 6660 << '\n';
#                 break;
#             }
#         }
# }