def collatz(n):
	z = [n]
	while n != 1:
		if n % 2 == 0:
			n = n/2
		else:
			n = 3*n+1
		z.append(n)
	return z

a = 0
for i in xrange(1,10**6):
	x = collatz(i)
	if len(x) > a:
		a = len(x)
		b = i

print(b)