def gcd(a,b):
	while b != 0:
		a, b = b, a % b
	return a

def coprime(a, b):

	def gcd(a, b):
		while b != 0:
			a, b = b, a % b
		return a

	return gcd(a, b) == 1

def totient(n):
	count = 0
	for i in xrange(1,n+1):
		if gcd(n,i) == 1:
			count += 1
	return count

def checkpermutation(a,b):
	from collections import Counter
	return len(a) == len(b) and len(a) > 1 and Counter(a) == Counter(b)

ratio = 1000

for m in xrange(1,501):
	for n in xrange(1,501):
		if coprime(m,n) is True:

			phi_m = totient(m)
			phi_n = totient(n)

			if  m/float(phi_m) < ratio and checkpermutation(str(phi_m),str(m)) is True:
				ratio = m/float(phi_m)
				print(m,phi_m,ratio)
	
			if n/float(phi_n) < ratio and checkpermutation(str(phi_n),str(n)) is True:
				ratio = n/float(phi_n)
				print(n,phi_n,ratio)

			if (m*n)/float(phi_m*phi_n) < ratio and checkpermutation(str(phi_m*phi_n),str(m*n)) is True:
				ratio = (m*n)/float(phi_m*phi_n)
				print(m*n,phi_m*phi_n,ratio)

#########CYTHON_VERSION###############

cdef gcd(int a, int b):
	while b != 0:
		a, b = b, a % b
	return a

cdef coprime(int a, int b):
	return gcd(a, b) == 1

cdef totient(int n):
	cdef int count
	cdef int i
	count = 0
	for i in xrange(1,n+1):
		if gcd(n,i) == 1:
			count += 1
	return count

cdef checkpermutation(a,b):
	from collections import Counter
	return len(a) == len(b) and len(a) > 1 and Counter(a) == Counter(b)

cdef float ratio
cdef int m
cdef int n
cdef int phi_m
cdef int phi_n

ratio = 1000.5

for m in xrange(1,4001):
	for n in xrange(m,4001):
		if coprime(m,n) is True:

			phi_m = totient(m)
			phi_n = totient(n)

			if  m/float(phi_m) < ratio and checkpermutation(str(phi_m),str(m)) is True:
				ratio = m/float(phi_m)
				print(m,phi_m,ratio)
	
			if n/float(phi_n) < ratio and checkpermutation(str(phi_n),str(n)) is True:
				ratio = n/float(phi_n)
				print(n,phi_n,ratio)

			if (m*n)/float(phi_m*phi_n) < ratio and checkpermutation(str(phi_m*phi_n),str(m*n)) is True:
				ratio = (m*n)/float(phi_m*phi_n)
				print(m*n,phi_m*phi_n,ratio)

################

#solved, took around 15 min using Cython
#Solution = n = 8319823 (phi(n) = 8313928)


# C++

#include <eulerlib.h>
#include <iostream>
#include <string>
#include <algorithm>

# std::string str;
# double tot, minimum = 100;

# int main()
# {
#     auto const primes = euler::sieve(10'000);
    
#     for (size_t num = 2; num < 10'000'000; ++num)
#     {
#         tot = euler::totient(num, primes);

#         if ((num / tot) < minimum)
#         {
#             str = std::to_string(num);

#             if (is_permutation(str.begin(), str.end(), std::to_string(tot).begin()))
#             {
#                 minimum = num / tot;
#                 std::cout << num << '\n';
#             }
#         }
#     }
# }
