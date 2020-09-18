from math import sqrt; from itertools import count, islice

def isprime(n):
	return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

A = 10**4

primelist = []
for i in xrange(1,A):
	if isprime(i) is True:
		primelist.append(i)

for i in xrange(1,A):

	a = False

	if i % 2 == 1 and isprime(i) is False:

		for j in primelist:

			for k in xrange(1,int(A**0.5)+2):

				if i == j + 2*k**2:
					a = True

		if a is False:
			print("%s is not ok!" % (i))