def fibonacci(n):
	a = 0; b = 1
	for i in xrange(1,n):
		b, a = a+b, b
	return b

n = 1
while True:
	x = fibonacci(n)
	if len(str(x)) == 1000:
		print(n)
		break
	else:
		n += 1

#Solved