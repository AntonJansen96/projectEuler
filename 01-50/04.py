z = []
for i in xrange(1,1000):
	for j in xrange(1,1000):
		product = i*j
		if str(product) == str(product)[::-1]:
			z.append(product)

print(sorted(z)[len(z)-1])