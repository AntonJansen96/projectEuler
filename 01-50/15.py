def binom(N,n):

	def factorial(n):
		g = 1
		for i in xrange(1,n+1):
			g *= i
		return g

	num = factorial(N)
	denom = factorial(n)*factorial(N-n)
	return num/denom

for i in xrange(1,21):
	a = binom(2*i,i)
	print("Lattice dimension: %s, Possible paths: %s" % (i,a))