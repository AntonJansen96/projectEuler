import fractions; from fractions import Fraction

def square_root_2(iterations):
	a = Fraction(1,2); b = 0

	for i in xrange(1,iterations):
		b = a
		a = Fraction(1,2+b)
	return 1 + a

def checkfraction(frac):
	if len(str(frac.numerator)) > len(str(frac.denominator)):
		return True
	else:
		return False

count = 0
for i in xrange(1,1001):
	print(i)
	if checkfraction(square_root_2(i)) is True:
		count += 1

print(count)