def chakravala(N):

	def cycle(a,b,k,N):
		minimal = 10**10
		for m in xrange(1,10**4):
			if (a+b*m) % k == 0:
				if abs(m**2-N) < minimal:
					minimal = abs(m**2-N)
					min_m   = m
		a,b,k = (a*min_m+N*b)/abs(k),(a+b*min_m)/abs(k),(min_m**2-N)/k
		return a,b,k

	def find_suitable_initial(N):
		minimal = 10**5

		for a in xrange(1,1000):
			for b in xrange(1,1000):
				k = abs(a**2 -N *b**2)
				if k < minimal:
					minimal = k
					mem_a = a
					mem_b = b

		return mem_a, mem_b, mem_a**2-N*mem_b**2

	a,b,k = find_suitable_initial(N)

	while True:
		if k == 0:
			return 0,0
		
		a,b,k = cycle(a,b,k,N)
		
		if k == 1:
			return a,b

largest = 0
for i in xrange(0,1001):
	x,y = chakravala(i)
	if x > largest:
		largest = x
		print(i,x)

#Solved, but algorithm is not perfect, FUCKING divide by zero (answer = 661, runtime few minutes)