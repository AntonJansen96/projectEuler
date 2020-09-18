from math import sqrt; from itertools import count, islice

def isprime(n):
	return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

def cycle(number,times):
	for i in xrange(0,times):
		
		number = str(number)
		last   = number[len(number)-1]
		new    = last+number[0:len(number)-1]
		number = int(new)

	return number

number = 0

for i in xrange(1,10**6):
	
	if isprime(i) is True:

		a = str(i)

		if len(a) == 1:
			number += 1

		elif len(a) == 2 and isprime(cycle(i,1)) is True:
			number += 1

		elif len(a) == 3 and isprime(cycle(i,1)) is True and isprime(cycle(i,2)) is True:
			number += 1

		elif len(a) == 4 and isprime(cycle(i,1)) is True and isprime(cycle(i,2)) is True and isprime(cycle(i,3)) is True:
			number += 1

		elif len(a) == 5 and isprime(cycle(i,1)) is True and isprime(cycle(i,2)) is True and isprime(cycle(i,3)) is True and isprime(cycle(i,4)) is True:
			number += 1

		elif len(a) == 6 and isprime(cycle(i,1)) is True and isprime(cycle(i,2)) is True and isprime(cycle(i,3)) is True and isprime(cycle(i,4)) is True and isprime(cycle(i,5)) is True:
			number += 1

print(number)