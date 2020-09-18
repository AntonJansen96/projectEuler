def gcd(a,b):
	while b != 0:
		a, b = b, a % b
	return a

def totient(n):
	count = 0
	for i in xrange(1,n+1):
		if gcd(n,i) == 1:
			count += 1
	return count

largest = 0
for i in xrange(1,10**4):
	x = float(i)/totient(i)
	if x > largest:
		largest = x
		print(i,largest)