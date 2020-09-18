#The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
#Find the sum of all the primes below two million.

from math import sqrt; from itertools import count, islice

def isPrime(n):
    return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

g = 0
for i in xrange(1,2*10**6+1):
	if isPrime(i) is True:
		g = g + i

print(g)

#Solved