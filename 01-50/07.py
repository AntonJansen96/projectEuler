from math import sqrt; from itertools import count, islice
def isprime(n):
	return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

n = 1
z = 0
while True:
	if isprime(n) is True:
		z += 1
	if z == 10001:
		print(n)
		break
	n += 1