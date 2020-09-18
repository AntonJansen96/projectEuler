def diag1(n):
	return 1 + (n+1)**2 - (2*(n+1) - ((n+1)%2))

def diag2(n):
	if n == 1:
		return 1
	if n == 2:
		return 3
	else:
		return n*(n-1)+1

total = 0
for i in xrange(1,1002):
	total += diag1(i) + diag2(i)

print(total-1)