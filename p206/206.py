#     1_2_3_4_5_6_7_8_9_0
#ind  0123456789112345678

def check(n):
	n = str(n)
	
	if len(str(n)) == 19 and n[0] == '1' and n[2] == '2' and n[4] == '3' and n[6] == '4' and n[8] == '5' and n[10] == '6' and n[12] == '7' and n[14] == '8' and n[16] == '9' and n[18] == '0':
		return True
	
	else:
		return False

for i in xrange(1,10**12):
	if check(i**2) is True:
		print(i)
		break