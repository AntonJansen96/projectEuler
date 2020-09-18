a = xrange(1,1001)
b = xrange(1,1001)

for i in xrange(0,1000):
	for j in xrange(0,1000):
		c = (a[i]**2 + b[j]**2)**0.5
		if a[i] + b[j] + c == 1000:
			print(a[i]*b[j]*c)

#Solved