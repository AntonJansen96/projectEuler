def isprime(n):		#Fast Enough
	if n > 2:
		if n % 2 == 0:
			return False
		for i in xrange(3,int(n**0.5)+1,2):
			if n % i == 0:
				return False
		return True
	if n == 2:
		return True
	return False

def primefactors(n):	#Needs optimization
	i = 2
	factors = []
	while i * i <= n:
		if n % i:
			i += 1
		else:
			n //= i
			factors.append(i)
	if n > 1:
		factors.append(n)

	return sorted(list(set(factors)))

def admissable(n):		#Assumes input = only even numbers, powers of 2 taken care of.
	factors = primefactors(n)

	for i in xrange(0,len(factors)-1):
		n = factors[i] + 1
		
		while True:
			if isprime(n) is True:
				if n == factors[i+1]:
					break
				else:
					return False
			n += 1

	return True

def pseudo_fortunate(n):		#Correct, fast enough
	y = n + 2
	while True:
		if isprime(y) is True:
			return y - n
		y += 1


#MAIN CODE


distinct_pfn = []

for i in xrange(0,10**6,2):								#Only for even numbers...
	if admissable(i) is True:							#that are admissable,
		a = pseudo_fortunate(i)							#calculate pseudo-fortunate number.
		#print(a)
		if a not in distinct_pfn:						#Check if this number is distinct and
			distinct_pfn.append(a)						#if it is distinct, add to list

print(sorted(distinct_pfn))
print(sum(distinct_pfn))

#Solved.
#Script took 156 min to run in cython.
#Script gives solution = 2211.
#This solution is incorrect. I tried 2212, 2210, 2209. 2209 appeared to be correct.
#I guesstimated this problem.