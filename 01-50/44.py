def pentagonal(n):
	return n*(3*n-1)/2

def pentagonal_list(n):
	g = []
	for i in xrange(1,n+1):
		g.append(pentagonal(i))
	return g

def checkpen(n):
	a = (1/6.0)*(1+(1+24*n)**0.5)
	if a.is_integer() is True:
		return True
	else:
		return False

A = pentagonal_list(10**4)

D  = 10**100

for i in A:
	for j in A:
		if i > j and checkpen(i+j) is True and checkpen(i-j) is True and i-j < D:
			D = i-j
			print(D)

#Solved (5482660)