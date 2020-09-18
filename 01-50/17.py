# 1 - 19

A = {
1 : 'one',
2 : 'two',
3 : 'three',
4 : 'four',
5 : 'five',
6 : 'six',
7 : 'seven',
8 : 'eight',
9 : 'nine',
10 : 'ten',
11 : 'eleven',
12 : 'twelve',
13 : 'thirteen',
14 : 'fourteen',
15 : 'fifteen',
16 : 'sixteen',
17 : 'seventeen',
18 : 'eighteen',
19 : 'nineteen',
}

g = 0
for  i in xrange(1,20):
	print(A[i])
	g = g + len(A[i])

total = g

#20 - 99

g = 0
for i in ['twenty','thirty','forty','fifty','sixty','seventy','eighty','ninety']:
	for j in xrange(0,10):
		if j == 0:
			print(i)
			g = g + len(i)
		else:
			q = i+A[j]
			print(q)
			g = g + len(q)

total = total + g

#100 - 999

g = 0
for i in ['onehundred','twohundred','threehundred','fourhundred','fivehundred','sixhundred','sevenhundred','eighthundred','ninehundred']:
	print(i)
	g = g + len(i)
	for j in xrange(1,20):
		print(i+'and'+A[j])
		g = g + len(i+'and'+A[j])
	for k in ['twenty','thirty','forty','fifty','sixty','seventy','eighty','ninety']:
		print(i+'and'+k)
		g = g + len(i+'and'+k)
		for m in xrange(1,10):
			print(i+'and'+k+A[m])
			g = g + len(i+'and'+k+A[m])

total = total + g

#1000

g = 0
print('onethousand')
g = g + len('onethousand')
total = total + g

print(total)

#Solved (sort of?) does not match exactly.