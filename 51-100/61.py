#IMPORT MODULES


import numpy as np
from itertools import permutations


#GENERATE LIST 


def triangle(n):
	return n*(n+1)/2

def square(n):
	return n**2

def pentagonal(n):
	return n*(3*n-1)/2

def hexagonal(n):
	return n*(2*n-1)

def heptagonal(n):
	return n*(5*n-3)/2

def octagonal(n):
	return n*(3*n-2)

z = []
for i in xrange(1,201):

	a = triangle(i)
	if len(str(a)) == 4 and a not in z:
		z.append(a)

	a = square(i)
	if len(str(a)) == 4 and a not in z:
		z.append(a)

	a = pentagonal(i)
	if len(str(a)) == 4 and a not in z:
		z.append(a)

	a = hexagonal(i)
	if len(str(a)) == 4 and a not in z:
		z.append(a)

	a = heptagonal(i)
	if len(str(a)) == 4 and a not in z:
		z.append(a)

	a = octagonal(i)
	if len(str(a)) == 4 and a not in z:
		z.append(a)

list1 = sorted(z)


#FUNCTIONS


def checkcyclic3(A):

	#Check in between
	
	for i in xrange(0,2):
		if str(A[i])[2:] != str(A[i+1])[:2]:
			return False

	return True


def checkcyclic4(A):

	#Check in between
	
	for i in xrange(0,3):
		if str(A[i])[2:] != str(A[i+1])[:2]:
			return False

	return True


def checkcyclic6(A):

	#Check first-last

	if str(A[5])[2:] != str(A[0])[:2]:
		return False 

	#Check in between
	
	for i in xrange(0,5):
		if str(A[i])[2:] != str(A[i+1])[:2]:
			return False

	return True


#FIND ALL 3 CYCLIC 4-DIGIT NUMBERS


cyclics_3 = []

for a in list1:
	for b in list1:
		for c in list1:
			if checkcyclic3([a,b,c]) is True:
				cyclics_3.append([a,b,c])


#FIND ALL 4 CYCLIC 4-DIGIT NUMBERS


cyclics_4 = []

for a in list1:
	for b in cyclics_3:
			z = []; z.append(a)
			if checkcyclic4(z+b) is True:
				cyclics_4.append(z+b)


#FIND ALL 6 CYCLIC 4-DIGIT NUMBERS


cyclics_6 = {}

for a in list1:
	for b in list1:
		for c in cyclics_4:
			x = []; x.append(a)
			y = []; y.append(b)
			if checkcyclic6(x+c+y) is True:
				som = np.sum(x+c+y)
				cyclics_6[som] = x+c+y


#FIND THE 6 CYCLIC 4-DIGIT NUMBER IN WHICH EACH POLYGON IS REPRESENTED


triangle_list   = []
square_list     = []
pentagonal_list = []
hexagonal_list  = []
heptagonal_list = []
octagonal_list  = []

for i in xrange(1,201):

	triangle_list.append(triangle(i))
	square_list.append(square(i))
	pentagonal_list.append(pentagonal(i))
	hexagonal_list.append(hexagonal(i))
	heptagonal_list.append(heptagonal(i))
	octagonal_list.append(octagonal(i))


list_values = [i for i in cyclics_6.values()]

for j in list_values:

	perms = list(permutations(j))

	for k in perms:

		if k[0] in triangle_list and k[1] in square_list and k[2] in pentagonal_list and k[3] in hexagonal_list and k[4] in heptagonal_list and k[5] in octagonal_list:
			print(cyclics_6[np.sum(k)],np.sum(k))


#Solved (28684)
#Runtime = 8min