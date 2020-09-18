def binom(N,n):

	def factorial(n):
		g = 1
		for i in xrange(1,n+1):
			g *= i
		return g

	num = factorial(N)
	denom = factorial(n)*factorial(N-n)
	return num/denom

count = 0
for N in xrange(1,101):
	for n in xrange(1,101):
		if binom(N,n) > 10**6:
			count += 1

print(count)