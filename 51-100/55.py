def palindrome(n):
	if str(n) == str(n)[::-1]:
		return True
	else:
		return False

def process(n):
	return n+int(str(n)[::-1])


count = 0

for i in xrange(1,10**4):
	
	n = i

	# if palindrome(n) is True:
	# 	count += 1
	# 	continue
	
	# else:
		
	iteration = 1
	
	while iteration < 50:
		
		n = process(n)
		
		if palindrome(n) is True:
			count += 1
			iteration = 100
		else:
			iteration += 1

print("Amount of Palindromes under 10000: %s" % (count))
print("Amount of Lychrel numbers under 10000: %s" % (9999-count))