# 75 - SINGULAR INTEGER RIGHT TRIANGLES

def gcd(a, b):
	while b != 0:
		a, b = b, a % b
	return a

limit = 1500000					# y = 2*m*n and max(y) == limit then
maxm = int((limit/2)**0.5)		# limit = 2*max(m)*max(n) = 2*max(m)*max(m) = 2*max(m)**2
								# max(m)**2 = limit/2 => max(m) = (limit/2)**0.5

A = limit * [0]					# List of occurences of all possible lengths < limit

for m in xrange(1, maxm):
	for n in xrange(1, maxm):
		if m > n:							# if m > n > 0 and
			if (m+n) % 2 == 1:				# m,n not both odd and
				if gcd(m,n) == 1:			# m,n are coprime (=> gcd(m,n) = 1) then:

					P = 2*m*(m+n) 			# a+b+c = (m**2-n**2) + (2*m*n) + (m**2+n**2) = 2*m**2 + 2*m*n = 2*m*(m+n)

					if P <= limit:
						for i in xrange(P,limit,P):		# Generate all non-primitve triples associated
							A[i] += 1					# with the primitive one we just calculated
														# This corresponds to using all values of k such that k*P <= limit
print(A.count(1))

#include <eulerlib.h>
#include <iostream>

# int main()
# {
#     auto const [A, B, C] = euler::genTriples(1'500'000);

#     std::vector<size_t> solcount(1'500'000, 0);

#     for (size_t idx = 0; idx != A.size(); ++idx)
#         ++solcount[A[idx] + B[idx] + C[idx]];

#     size_t unique = 0;
#     for (size_t sol : solcount)
#         if (sol == 1)
#             ++unique;

#     std::cout << unique << '\n';
# }
