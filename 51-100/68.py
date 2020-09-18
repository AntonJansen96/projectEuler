#maximum 16-digit string, so the number '10' is in one of  the outer circles
#we work clockwise, starting from the numerically lowest external node

largest = 0

for A in xrange(1,11):
	for B in xrange(1,11):
		if B != A:
			for C in xrange(1,11):
				if C not in [A,B]:
					for D in xrange(1,11):
						if D not in [A,B,C]:
							for E in xrange(1,11):
								if E not in [A,B,C,D]:
									for F in xrange(1,11):
										if F not in [A,B,C,D,E]:
											for G in xrange(1,11):
												if G not in [A,B,C,D,E,F]:
													for H in xrange(1,11):
														if H not in [A,B,C,D,E,F,G]:
															for I in xrange(1,11):
																if I not in [A,B,C,D,E,F,G,H]:
																	for J in xrange(1,11):
																		if J not in [A,B,C,D,E,F,G,H,I]:
																			if A < D and A < F and A < H and A < J:
																				solution = str(A)+str(B)+str(C)+str(D)+str(C)+str(E)+str(F)+str(E)+str(G)+str(H)+str(G)+str(I)+str(J)+str(I)+str(B)
																				if len(solution) == 16 and A+B+C == D+C+E and D+C+E == G+E+F and G+E+F == I+G+H and I+G+H == J+I+B and int(solution) > largest:
																					largest = int(solution)
																					print(largest)