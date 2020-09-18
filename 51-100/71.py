def HCF(a,b):
	while b != 0:
		a, b = b, a % b	
	return a

mem_n = mem_b = 0
largest = 0.0
frac = 3/float(7)

for n in xrange(1,10**3):
	for d in xrange(n+1,10**3+1):		#n < d
		
		if HCF(n,d) != 1:				#HCF(n,d)=1
			continue

		y = n/float(d)					#Calculate n/d

		if y < frac and y > largest:	#Check if n/d smaller than 3/7,
										#But larger than the number closest to 3/7
			mem_n   = n
			mem_d   = d
			largest = y
			continue

		if y < largest:
			break

print(largest,"%s/%s" % (mem_n,mem_d))