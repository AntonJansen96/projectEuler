x = y = 0
for i in xrange(1,101):
	x += i**2
	y += i
print(abs(x - y**2))