#The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.
#Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
#(Please note that the palindromic number, in either base, may not include leading zeros.)

def dec_to_bin(n):
	return int(bin(n)[2:])

total = 0

for i in xrange(1,10**6):

	if str(i) == str(i)[::-1] and str(dec_to_bin(i)) == str(dec_to_bin(i))[::-1]:
		print(i,dec_to_bin(i))
		total += i

print(total)