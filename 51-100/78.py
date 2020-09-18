# COIN PARTITIONS

# import fractions

# def partitions(number):

# 	def DivisorSigma(n,k):

# 		def divisors(n):
# 			g = []
# 			for i in xrange(1,n/2+1):
# 				if n % i == 0:
# 					g.append(i)
# 			return g+[n]

# 		divs = divisors(n)

# 		count = 0
# 		for i in xrange(0, len(divs)):
# 			count += (divs[i])**k

# 		return count

# 	Sigmas = [0]*number
# 	for i in xrange(0, number):
# 		Sigmas[i] = DivisorSigma(i+1, 1)

# 	Ps = [1]*(number+1)
# 	for n in xrange(2, number+1):
# 		print(n)
# 		count = 0
# 		for k in xrange(0, n):
# 			count += Sigmas[n-k-1]*Ps[k]
# 		# Ps[n] = int((1/float(n))*count)
# 		Ps[n] = fractions.Fraction(1,n)*fractions.Fraction(count,1)
		
# 		if Ps[n] % 10**6 == 0:
# 			print('answer: %s' % (n))
# 			break

# 	return Ps[number]

# partitions(10**5)

# solved (55374)
# Took 2.5 hours to run

Parti = [1, 1]

def P(n, L = Parti):
	k = 1; nb = 0; i = 1
	
	while n - i >= 0:
		nb += (-1)**(k - 1) * L[n - i]
		
		if n - i - k >= 0:
			nb += (-1)**(k-1) * L[n - i - k]
		
		k += 1
		i = int(k * (3 * k - 1) / 2)
	
	L.append(nb)
	return nb

n = 2
while P(n) % 10**6 != 0:
	n += 1

print(n)
