def isprime(n):
	from math import sqrt; from itertools import count, islice
	return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

def cycles(n):
	return (10**(n-1)-1)/n

for i in xrange(1,1001):
	
	if isprime(i) is True:

		print(i,1.0/i,cycles(i))

#https://en.wikipedia.org/wiki/Repeating_decimal
#https://oeis.org/A001913

#Solved (983)