def isprime(n):
	from math import sqrt; from itertools import count, islice
	return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

def diag1(n):
	return 1 + (n+1)**2 - (2*(n+1) - ((n+1)%2))

def diag2(n):
	if n == 1:
		return 1
	if n == 2:
		return 3
	else:
		return n*(n-1)+1

prime = total = 0

for i in xrange(1,10**8):

	if isprime(diag1(i)) is True:
		prime += 1

	if isprime(diag2(i)) is True:
		prime += 1

	total += 2

	ratio = prime/float(total-1)
	
	if ratio < 0.1 and i != 1:
		print(i)
		break