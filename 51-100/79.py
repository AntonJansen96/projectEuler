A = [319,680,180,690,129,620,762,689,762,318,368,710,720,710,629,168,160,689,716,731,736,729,316,729,729,710,769,290,719,680,318,389,162,289,162,718,729,319,790,680,890,362,319,760,316,729,380,319,728,716]

first = []
second = []
third = []
for i in A:
	first.append(int(str(i)[0]))
	second.append(int(str(i)[1]))
	third.append(int(str(i)[2]))

print("first number: ")
for i in [1,2,3,6,7,8,9,0]:
	print(i,first.count(i),first.count(i)/float(50))

print("second number: ")
for i in [1,2,3,6,7,8,9,0]:
	print(i,second.count(i),second.count(i)/float(50))

print("third number: ")
for i in [1,2,3,6,7,8,9,0]:
	print(i,third.count(i),third.count(i)/float(50))

#4 and 5 are not in the password

# 73612890		#wrong

# 73162890		#correct

#Solved