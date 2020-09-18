g = 0
for i in xrange(1,1001):
	g += i**i

g = str(g)

print(g[len(g)-10:len(g)])