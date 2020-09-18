def properdivisors(n):
	g = []
	for i in xrange(1,n/2+1):
		if n%i == 0:
			g.append(i)
	return g

def propdivsum(n):
	g = 0
	for i in xrange(1,n/2+1):
		if n%i == 0:
			g = g + i
	return g

g = 0
for i in xrange(1,10000):
	for j in xrange(1,10000):
		if i != j and propdivsum(i) == j and propdivsum(j) == i:
			g = g + i

print(g)

#Solved

print(properdivisors(220))