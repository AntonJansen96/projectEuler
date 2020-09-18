def checkpan(n):
	if len(str(n)) != 9:
		return False
	elif sorted(str(n)) == ['1','2','3','4','5','6','7','8','9']:
		return True
	else:
		return False

largest = 0

for i in xrange(1,10**6):
	
	g = ""
	for j in xrange(1,10):
		g += str(j*i)

		if checkpan(int(g)) is True and int(g) > largest:
			largest = int(g)
			print(largest)

#Solved (932718654)