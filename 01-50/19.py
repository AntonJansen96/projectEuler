def first_day_year(year):
	
	if year == 1900:
		return 0

	else:
		years = year - 1900
		days  = 365*years

		leapdays = 0
		for i in xrange(1901,year):
			if i % 4 == 0:
				leapdays = leapdays + 1

		days = days + leapdays

		week_remainder = days % 7

		return int(week_remainder)

A      = ['jan','feb','mar','apr','may','jun','jul','aug','sep','okt','nov','dec']
X      = ["monday","tuesday","wednesday","thursday","friday","saturday","sunday"]

B      = [31,28,31,30,31,30,31,31,30,31,30,31]
Bleap  = [31,29,31,30,31,30,31,31,30,31,30,31]

file_object = open("output.txt", "w")

for i in range(1901,2001):
	
	remainder = first_day_year(i)
	z = -1

	if i % 4 == 0 and i != 1900:
		for j in range(0,12):
			for k in range(1,Bleap[j]+1):
				z = z + 1
				file_object.write("%s%s%s%s\n" % (i,A[j],k,X[(remainder + z) % 7])) 
	else:
		for j in range(0,12):
			for k in range(1,B[j]+1):
				z = z + 1
				file_object.write("%s%s%s%s\n" % (i,A[j],k,X[(remainder + z) % 7]))

file_object.close()

file_object = open("output.txt", "r")
A = file_object.read()

g = 0
for i in ['jan1sunday','feb1sunday','mar1sunday','apr1sunday','may1sunday','jun1sunday',
		 'jul1sunday','aug1sunday','sep1sunday','okt1sunday','nov1sunday','dec1sunday']:
	g = g + A.count(i)

print(g)

file_object.close()

#Solved