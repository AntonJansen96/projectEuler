# 87 - PRIME POWER TRIPLES

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

###############################

limit = 50*10**6

# # GEN PRIME SQUARE LIST

P1 = []
for i in xrange(1, int(limit**0.5)+1):
	if isprime(i) is True:
		P1.append(i**2)

# GEN PRIME CUBE LIST

P2 = []
for i in xrange(1, int(limit**0.33333)+1):
	if isprime(i) is True:
		P2.append(i**3)

# GEN PRIME FOURTH-POWER LIST

P3 = []
for i in xrange(1, int(limit**0.25)+1):
	if isprime(i) is True:
		P3.append(i**4)

# BRUTE FORCE

A = [0]*limit

for i in P1:
	for j in P2:
		for k in P3:
			x = i+j+k
			if x < limit:
				A[x] += 1

print(limit - A.count(0))

# 1097343 is correct
