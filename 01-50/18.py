""""Project Euler problem 18 - Finding largest path in a pyramid"""

from random import randint

A=                  [75]							#The Pyramid
B=                 [95,64]
C=               [17,47,82]
D=              [18,35,87,10]
E=             [20,4,82,47,65]
F=            [19,1,23,75,3,34]
G=           [88,2,77,73,7,63,67]
H=         [99,65,4,28,6,16,70,92]
I=       [41,41,26,56,83,40,80,70,33]
J=     [41,48,72,33,47,32,37,16,94,29]
K=    [53,71,44,65,25,43,91,52,97,51,14]
L=   [70,11,33,28,77,73,17,78,39,68,17,57]
M=  [91,71,52,38,17,14,91,43,58,50,27,29,48]
N= [63,66,4,68,89,53,67,30,73,16,69,87,40,31]
O=[4,62,98,27,23,9,70,98,73,93,38,53,60,4,23]

largest = 0

for j in xrange(1,10**6):							#Amount of tries

	for i in [A,B,C,D,E,F,G,H,I,J,K,L,M,N,O]:		#Loop through all rows of the pyramid
		
		if i == A:									#Special case for 1st row
			x = A[0]
			#print(x)
		
		elif i == B:								#Special case for 2nd row
			a = randint(0,1)
			x = x + B[a]
			index = a
			#print(B[a])

		else:										#Loop through remaining rows
			y = []
			y.append(i[index]); y.append(i[index+1])
			a = randint(0,1)
			#print(y[a])
			x = x + y[a]
			index = i.index(y[a])

	if x > largest:									#Update largest if it finds a larger path
		largest = x
		print(largest)								#Print new path if it found a larger one

#Solved but not efficient for large pyramids