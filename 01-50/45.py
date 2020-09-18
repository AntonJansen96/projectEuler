def checktriang(n):
	a = (1/2.0)*(-1+(1+8*n)**0.5)
	if a.is_integer() is True:
		return True
	else:
		return False

def checkpen(n):
	a = (1/6.0)*(1+(1+24*n)**0.5)
	if a.is_integer() is True:
		return True
	else:
		return False

def checkhex(n):
	a = (1/4.0)*(1+(1+8*n)**0.5)
	if a.is_integer() is True:
		return True
	else:
		return False

for i in xrange(1,10**12):
	if checktriang(i) is True and checkpen(i) is True and checkhex(i) is True:
		print(i)

#Solved (1533776805)