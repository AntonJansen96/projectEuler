def isprime(n):
	from math import sqrt; from itertools import count, islice
	return n > 1 and all(n%i for i in islice(count(2), int(sqrt(n)-1)))

def combinations(elements):
	
	def dec_to_bin(n):
		return int(bin(n)[2:])

	a = []
	for i in xrange(1,2**len(elements)-1):
		b = str(dec_to_bin(i))
		while len(b) != len(elements):
			b = '0'+b
		a.append(b)
	return a

def changenumber(number,infostring,digit):
	number    = str(number)
	newnumber = ""
	
	for i in xrange(0,len(number)):
		if infostring[i] == '1':
			newnumber = newnumber+str(digit)
		else:
			newnumber = newnumber+number[i]

	return int(newnumber)


#print(combinations([1,2,3]))

largest = 0

for i in xrange(1,200000):

	if isprime(i) is True:

		combis = combinations(range(0,len(str(i))))
		#print(i,combis)

		for j in combis:

			count = 0

			for k in xrange(0,10):
				
				prime = changenumber(i,j,k)
				#print(prime)

				if isprime(prime) is True and len(str(prime)) == len(str(i)):
					count += 1
					#print(i,count)

					# if count > largest:
					# 	largest = count
					# 	print(i,count)

			if count == 8:
				print(i,count)

#Solved