with open('input.txt') as f:
    w, h = [int(x) for x in next(f).split()]
    array = []
    for line in f:
        array.append([int(x) for x in line.split()])

array = [[59]]+[[73,41]]+array


#MAXIMUM-PATH SUM ALGORITHM


vector = array
vector = vector[::-1]

for j in xrange(0,len(vector)-1):

	for i in xrange(0,len((vector[j]))-1):

		a = (vector[j])[i]
		b = (vector[j])[i+1]

		if a >= b:
			(vector[j+1])[i] += a
		else:
			(vector[j+1])[i] += b

print((vector[len(vector)-1])[0])


#MAXIMUM-PATH SUM ALGORITHM