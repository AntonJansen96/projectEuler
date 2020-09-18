# 76 - COUNTING SUMMATIONS

def partitions(number):

	def DivisorSigma(n,k):

		def divisors(n):
			g = []
			for i in xrange(1,n/2+1):
				if n % i == 0:
					g.append(i)
			return g+[n]

		divs = divisors(n)

		count = 0
		for i in xrange(0, len(divs)):
			count += (divs[i])**k

		return count

	Sigmas = [0]*number
	for i in xrange(0, number):
		Sigmas[i] = DivisorSigma(i+1, 1)

	Ps = [1]*(number+1)
	for n in xrange(2, number+1):
		count = 0
		for k in xrange(0, n):
			count += Sigmas[n-k-1]*Ps[k]
		Ps[n] = int((1/float(n))*count)

	return Ps[number]

print(partitions(100) + 1)
