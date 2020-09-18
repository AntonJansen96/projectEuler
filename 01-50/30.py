import numpy as np

z = []

for i in xrange(2,10**7):
	
	g = 0
	
	for j in str(i):
		g = g + int(j)**5

	if i == g:
		z.append(i)

print(z)
print(np.sum(z))

#Solved