from itertools import permutations
from math import sqrt; from itertools import count, islice

def isprime(n):
	return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

largest = 0

A = list(permutations([1,2,3,4,5,6,7]))		#All pandigital permutations

for i in xrange(0,len(A)):
	
	g = ""
	x = A[i]
	
	for j in xrange(0,7):
		g = g+str(x[j])

	g = int(g)									#Pandigital permutation conv. to number

	if isprime(g) is True and g > largest:
		largest = g
		print(largest)

#Solved(7652413)