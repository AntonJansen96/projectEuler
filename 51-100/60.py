def isprime(n):
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

def primelist(size):
	g = []
	for i in xrange(1,size):
		if isprime(i) is True:
			g.append(i)
	return g

def check_coc(A):
	for i in A:
		for j in xrange(0,len(A)):
			if i != A[j]:
				if isprime(int(str(i)+str(A[j]))) is True and isprime(int(str(A[j])+str(i))) is True:
					continue
				return False
	return True

#SET PRIME UPPER LIMIT (IF NO RESULTS FOUND)
print("building primelist...")

primes1 = primelist(10**3)

#FIND ALL 2-SETS:
print("finding 2-sets...")

twosets = []

for i in primes1:
	primes2 = primes1[primes1.index(i)+1:]
	
	for j in primes2:
		
		x = sorted([i,j])
		if check_coc(x) is True and x not in twosets:
			twosets.append(x)

#FIND ALL 3-SETS:
print("finding 3-sets...")

threesets = []

for i in primes1:
	for j in twosets:
		if i not in j:
			x = sorted([i]+j)
			if check_coc(x) is True and x not in threesets:
				threesets.append(x)

#FIND ALL 4-SETS:
print("finding 4-sets...")

foursets = []

for i in primes1:
	for j in threesets:
		if i not in j:
			x = sorted([i]+j)
			if check_coc(x) is True and x not in foursets:
				foursets.append(x)

#FIND ALL 5-SETS:
print("finding 5-sets...")

fivesets = []

for i in primes1:
	for j in foursets:
		if i not in j:
			x = sorted([i]+j)
			if check_coc(x) is True and x not in fivesets:
				fivesets.append(x)

#FIND LOWEST SUM OF 5-SETS:

if fivesets == []:
	print("did not find any 5-sets")
else:
	print("finding lowest sum...")

	sums = []
	for i in fivesets:
		sums.append(sum(i))

	a = sorted(sums)

	print(a[0])
