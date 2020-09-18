# 64 - ODD PERIOD SQUARE ROOTS

def checksquare(x):
	if int(x**0.5) == x**0.5:
		return True
	return False

import decimal

decimal.getcontext().prec = 300						# Required precision depends on length of CF.
													# with largest periodicity.
limit = 10000
count = 0

for i in xrange(1, limit+1):
	if checksquare(i) is False:						# Squares do not count.

		sqrt     = decimal.Decimal(i).sqrt()		# Determine sqrt using decimal module with 300 digit precision.

		int_part = int(sqrt)						# Determine first integer part (part of CF algorithm).
		rem_part = sqrt - int_part					# Determine first remaining part (part of CF algorithm).

		coeff_index = 1
		while True:

			inv   = 1/rem_part						# CF algorithm.
			coeff = int(inv)						# CF algorithm.

			if coeff == 2*int_part:					# Core math trick of this problem: periodic sequence will always end
				if coeff_index % 2 == 1:			# with a number that is twice the first integer part for square roots.
					count += 1						# This however will not work for non-square-root CFs.
					break
				else:
					break

			rem_part = inv - coeff 					# CF algorithm.
			coeff_index += 1

print(count)

# Solved. Runs in 8s.
