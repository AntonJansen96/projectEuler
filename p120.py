def compute(a, n):
    return ((a-1)**n + (a+1)**n) % (a**2)

def maximumRemainder(a):
    Max = 0
    for n in range(1, 2*a):
        val = compute(a, n)
        
        if val > Max:
            Max = val
    
    return Max

# Assert example
# print(compute(7, 3))

# for n in range(1, 10):
#     print(n, compute(7, n))

# print(maximumRemainder(7))

total = 0
for a in range(3, 1001):
    print(a)
    total += maximumRemainder(a)

print(total)
