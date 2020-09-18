def samedigits(x,y):
	if sorted(str(x)) == sorted(str(y)):
		return True
	else:
		return False

n = 1
while True:
	if samedigits(n,2*n) is True and samedigits(n,3*n) is True and samedigits(n,4*n) is True and samedigits(n,5*n) is True and samedigits(n,6*n) is True:
		print(n)
		break

	n += 1