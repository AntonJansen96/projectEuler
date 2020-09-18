count = 0

for a in xrange(1,400):
	for b in xrange(1,400):
		if len(str(a**b)) == b:
			count += 1

print(count)