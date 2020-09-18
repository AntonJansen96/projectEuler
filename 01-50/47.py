def primefactors(n):
	i = 2
	factors = []
	while i * i <= n:
		if n % i:
			i += 1
		else:
			n //= i
			factors.append(i)
	if n > 1:
		factors.append(n)
	return list(set(factors))

for i in xrange(1,10**10):
	if len(primefactors(i)) == 4 and len(primefactors(i+1)) == 4 and len(primefactors(i+2)) == 4 and len(primefactors(i+3)) == 4:
		print(i)
		break