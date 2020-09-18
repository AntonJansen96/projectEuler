# 80 - SQUARE ROOT DIGITAL EXPANSION

def checksquare(x):
	if int(x**0.5) == x**0.5:
		return True
	return False

import decimal
decimal.getcontext().prec = 201

count = 0
for i in xrange(1,101):
	if checksquare(i) is False:

		number = decimal.Decimal(i).sqrt()
		number = str(number)
		
		for j in xrange(0,101):
			if number[j] != '.':
				count += int(number[j])

print(count)
