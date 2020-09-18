z = []
for a in xrange(2,101):
	for b in xrange(2,101):
		p = a**b
		if p not in z:
			z.append(p)
print(len(z))

#Solved