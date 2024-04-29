def check_reversible(n):
	if str(n)[len(str(n)) - 1] == '0':
		return False

	a = str(n + int(str(n)[::-1]))
	
	for i in a:
		if int(i) % 2 == 0:
			return False
	
	return True

count = 0

for i in range(1, 10**7):
	if check_reversible(i) is True:
		count += 1

print(count)
