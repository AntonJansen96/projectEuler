from itertools import permutations

A = list(permutations([0,1,2,3,4,5,6,7,8,9]))		#All pandigital permutations

total = 0

for i in xrange(0,len(A)):
	
	g = ""
	x = A[i]
	
	for j in xrange(0,10):
		g = g+str(x[j])

	if int(g[1:4]) % 2 == 0 and int(g[2:5]) % 3 == 0 and int(g[3:6]) % 5 == 0 and int(g[4:7]) % 7 == 0 and int(g[5:8]) % 11 == 0 and int(g[6:9]) % 13 == 0 and int(g[7:10]) % 17 == 0:
		total += int(g)

print(total)

#Solved