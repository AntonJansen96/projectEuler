count = 0          	 	# Stores sum of even FB numbers.

a = 0               	# n-1th FB number.
b = 1               	# nth FB number.

while b <= 4000000:
	a, b = b, a + b		# Find next FB number.

	if b % 2 == 0:  	# If FB is even, add it to count.
		count += b

print(count)
