solutions = pval = 0

for p in xrange(1,1001):
	
	sol = 0

	for a in xrange(1,p):
		for b in xrange(1,p):
					
				if ((a**2+b**2)**0.5).is_integer() is True and a+b+int((a**2+b**2)**0.5) == p:
					sol += 1

	if sol > solutions:
		solutions = sol
		pval = p

		print(pval,solutions)

#Solved