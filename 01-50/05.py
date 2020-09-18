x = range(11,21)
z = 20
a = 1

while 2 > a:
	for i in x:
		if z % i != 0:
			z = z + 1
			break
		elif i == 20:
			print(z)
			a = 3