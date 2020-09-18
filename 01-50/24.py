import itertools

a = list(itertools.permutations([0,1,2,3,4,5,6,7,8,9]))

z = []
for i in xrange(0,len(a)):
	g = ""
	for j in a[i]:
		g = g+str(j)
	z.append(int(g))
z.sort()

print(z[10**6-1])

#Solved