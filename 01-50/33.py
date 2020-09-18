import fractions; from fractions import Fraction

product = 1

for a in xrange(10,100):
	for b in xrange(10,100):
		
		common = None
		
		for i in str(a):
			if i in str(b):
				
				if str(a)[0] == str(b)[0]:
					common = str(a)[0]
				else:
					common = str(a)[1]
				
		if common != None and str(a)[0] != str(a)[1] and str(b)[0] != str(b)[1] and str(a) != str(b) and str(a)[1] != '0' and str(b)[1] != '0':
			
			a_updated = int(str(a).replace(common,""))
			b_updated = int(str(b).replace(common,""))
			
			if b_updated != 0:

				frac1 = Fraction(a,b)
				frac2 = Fraction(a_updated,b_updated)

				if frac1 == frac2:

					print("%s/%s" % (a,b))
					product *= frac1

print("Product: %s" % (product))

#Solved (100)