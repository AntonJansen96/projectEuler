#95 - AMICABLE CHAINS

def properdivisorsum(n):

	import itertools

	def accumulate(iterator):
		total = 0
		for item in iterator:
			total += item
			yield total

	def prime_powers(n):
		for c in accumulate(itertools.chain([2, 1, 2], itertools.cycle([2, 4]))):
			if c*c > n:
				break
			if n % c:
				continue
			d,p = (), c
			while not n % c:
				n, p, d = n//c, p*c, d + (p,)
			yield(d)
		if n > 1:
			yield((n,))

	r = [1]
	for e in prime_powers(n):
		r += [a*b for a in r for b in e]
	
	return sum(r)-n

# MAIN CODE #######################################################################

limit = 10**6
depth = 40

# GENERATE DIVISORSUM ARRAY FOR ALL NUBMERS SMALLER THAN ONE MILLION

PDS   = limit * [0]

for i in range(1, limit):
	PDS[i] = properdivisorsum(i)

# FIND SMALLEST NUMBER OF LONGEST CHAIN

max_length = 0
max_chain = []

for starting_number in range(1, limit):

	chain    = depth*[0]
	chain[0] = starting_number
	number   = starting_number

	index = 1
	while index < depth:

		try:
			number = PDS[number]
		except IndexError:
			break
	
		if number == starting_number:

			if (depth-chain.count(0)) > max_length:
				max_length = (depth-chain.count(0))
				max_chain  = chain
			break
	
		else:
			chain[index] = number
			index += 1

for i in range(max_chain.count(0)):
	max_chain.remove(0)

print(min(max_chain))

# solution 14316 (13 s)
