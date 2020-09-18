import math

def triang(n):
	return n*(n+1)/2

def divisorGenerator(n):
    large_divisors = []
    for i in xrange(1, int(math.sqrt(n) + 1)):
        if n % i == 0:
            yield i
            if i*i != n:
                large_divisors.append(n / i)
    for divisor in reversed(large_divisors):
        yield divisor

n = 1
while True:
	x = triang(n)
	y = list(divisorGenerator(x))
	if len(y) > 501:
		print(x)
		break
	n = n + 1

#Solved