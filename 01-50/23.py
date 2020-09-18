import numpy as np

def propdivsum(n):
	g = 0
	for i in xrange(1,n/2+1):
		if n%i == 0:
			g = g + i
	return g

def abundantGenerator(n):
	g = []
	for i in xrange(1,n+1):
		if propdivsum(i) > i:
			g.append(i)
	return g

A = 28123

q = abundantGenerator(int(A))

g = []
for i in q:
	for j in q:
		if i+j <= A and i+j not in g:
			g.append(i+j)

sum_g        = np.sum(g)
sum_total    = np.sum(xrange(1,A+1))
sum_solution = sum_total - sum_g

print("sum of numbers that can be written...: %s" % (sum_g))
print("sum of total: %s" % (sum_total))
print("sum of numbers that cannot be written...: %s" % (sum_solution))

#Solved
#Runtime = 16 minutes