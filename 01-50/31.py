cdef int a
cdef int b
cdef int c
cdef int d
cdef int e
cdef int f
cdef int g
cdef int count

count = 0
for a in xrange(0,201):
	for b in xrange(0,101):
		for c in xrange(0,41):
			for d in xrange(0,21):
				for e in xrange(0,11):
					for f in xrange(0,5):
						for g in xrange(0,3):
							if a+2*b+5*c+10*d+20*e+50*f+100*g == 200:
								count += 1

print(count+1)