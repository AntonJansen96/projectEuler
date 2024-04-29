#!/usr/bin/python3
import numpy as np

def generate(n):
    return 1 - n + n**2 - n**3 + n**4 - n**5 + n**6 - n**7 + n**8 - n**9 + n**10

def compute(coeffs, num):           # Compute an nth-degree polynomial for 
    answer = 0                      # the value num using the n-coefficients.
    for i in range(0, len(coeffs)):
        answer += coeffs[i] * num**i
    return int(answer)

FITsum = 0

for order in range(1, 11):         # For a 10th degree genenerating function.
    x = []; y = []                  
    for n in range(1, order + 1):  # Make x and y.
        x.append(n)
        y.append(generate(n))

    coeffs = np.polyfit(x, y, order - 1)               # Compute fitting coeffs.
    coeffs = [round(coeff) for coeff in coeffs][::-1]  # Round and reverse.
    
    FITsum += compute(coeffs, order + 1)        # Compute first wrong term
                                                # and add.
print(FITsum)
