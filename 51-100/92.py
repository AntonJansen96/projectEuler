def step(n):
	x = 0
	for i in str(n):
		x += int(i)**2
	return x

def check89(n):
 	while n != 1 and n != 89:
 		n = step(n)
 	if n == 89:
 		return True
 	else:
 		return False

count = 0

for i in xrange(1,10**7):
	if check89(i) is True:
		count += 1

print(count)