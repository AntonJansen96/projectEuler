largest = 0

with open("input.txt") as f:
    content = f.readlines()

explist = [x.strip() for x in content]

for i in explist:
	komma    = i.find(',')
	base     = int(i[:komma])
	exponent = int(i[komma+1:])
	
	a = base**exponent

	if a > largest:
		largest = a
		print(base,exponent)