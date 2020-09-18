# 65 - CONVERGENCE OF E

def CFgeneral(number,terms):
	int_part = int(number)
	rem_part = number - int_part

	Terms = [int_part]

	for i in xrange(1, terms+1):
		inv = 1/rem_part

		Terms.append(int(inv))

		coeff = int(inv)
		rem_part = inv - coeff

	return Terms

def rationalapproxCF(T):
	A = len(T)*[0]
	B = len(T)*[0]

	A[0] = 1;		B[0] = 0
	A[1] = T[0];  	B[1] = 1

	for i in xrange(2,len(T)):
		A[i] = T[i-1] * A[i-1] + A[i-2]
		B[i] = T[i-1] * B[i-1] + B[i-2]

	C = []
	for i in xrange(1, len(A)):
		C.append(fractions.Fraction(A[i], B[i]))

	return C

import decimal
import fractions

decimal.getcontext().prec = 300	

number = decimal.Decimal(1).exp()
limit  = 100

cont_frac	   = CFgeneral(number,limit)
rat_proc 	   = rationalapproxCF(cont_frac)
hundredth_term = rat_proc[99]
num_100th_term = hundredth_term.numerator

digitsum = 0
for i in str(num_100th_term):
	digitsum += int(i)

print(digitsum)
