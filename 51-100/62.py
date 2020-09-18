#IF TWO NUMBERS HAVE THE SAME DIGITS, THEY ARE PERMUTATIONS

def check_same_digits(a,b):
	if sorted(str(a)) == sorted(str(b)):
		return True
	return False

#GENERATE A LIST OF CUBE NUMBERS WITH SAME SAME # DIGTIS

def cubelist(digits):
	cubes = []
	n = 1
	while True:
		if len(str(n**3)) == digits:
			cubes.append(n**3)
		if len(str(n**3)) > digits:
			break
		n += 1
	return cubes

#MAIN CODE

for i in xrange(1,15):
	print(i)

	cubes1 = cubelist(i)

	for a in cubes1:
		cubes2 = cubes1[cubes1.index(a)+1:]
		
		for b in cubes2:
			if check_same_digits(a,b) is False:
				continue

			cubes3 = cubes2[cubes2.index(b)+1:]

			for c in cubes3:
				if check_same_digits(b,c) is False:
					continue

				cubes4 = cubes3[cubes3.index(c)+1:]

				for d in cubes4:
					if check_same_digits(c,d) is False:
						continue

					cubes5 = cubes4[cubes4.index(d):]

					for e in cubes5:
						if check_same_digits(d,e) is True and e not in [a,b,c,d]:
							print([a,b,c,d,e])
							print(sorted([a,b,c,d,e])[0])
							break

#Solved, runs in about 30 s