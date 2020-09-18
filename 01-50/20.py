def sum_digits(n):
    s = 0
    while n:
        s += n % 10
        n //= 10
    return s

def factorial(n):
	g = 1
	for i in xrange(1,n+1):
		g *= i
	return g

print(sum_digits(factorial(100)))

#Solved