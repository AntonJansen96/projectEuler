a = ""
for i in xrange(1,2*10**5):
	a += str(i)
	
b = 1
for i in [1,10,100,1000,10000,100000,1000000]:
	b *= int(a[i-1])

print(b)

#Solved (210)