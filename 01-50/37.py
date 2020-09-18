#The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right,
#and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
#Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
#NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

from math import sqrt; from itertools import count, islice

def isprime(n):
	return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

primes = total = 0
n      = 11

while primes != 11:

	if isprime(n) is True:

		versions = []
		a = str(n)

		for i in xrange(0,len(a)):		
				
			b = a[0:len(a)-i]			#From R to L
			c = a[i:len(a)]				#From L to R
			
			versions.append(int(b))
			versions.append(int(c))

		del versions[0]

		k = 0
		for i in versions:
			if isprime(i) is True:
				k += 1

		if k == len(versions):
			primes += 1
			total  += n

	n += 1

print(total)

#Solved (748317)