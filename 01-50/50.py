from math import sqrt; from itertools import count, islice

def isprime(n):
	return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

primelist = []
for i in xrange(1,10000):
	if isprime(i) is True:
		primelist.append(i)

largest = 0

for i in xrange(0,len(primelist)):
	
	consecutive = 0
	number = 0

	for j in xrange(i,len(primelist)):
		
		if number > 10**6:
			continue

		number += primelist[j]
		consecutive += 1

		if isprime(number) is True and consecutive > largest:
			largest = consecutive
			print("%s is made up of %s primes" % (number,consecutive))
