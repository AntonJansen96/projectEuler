def sum_digits(n):
    s = 0
    while n:
        s += n % 10
        n //= 10
    return s

largest = 0

for i in xrange(1,100):
	for j in xrange(1,100):

		if sum_digits(i**j) > largest:
			largest = sum_digits(i**j)
			print("%s, (%s^%s)" % (largest,i,j))