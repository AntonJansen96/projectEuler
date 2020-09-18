# def primefactors(i,f):		# f = 2
#     if i < f:
#         return []
#     if i % f == 0:
#         return [f] + primefactors (i / f, 2)
#     return primefactors (i, f + 1)

# print(primefactors(600851475143,2))

def primefactors(n):
    i = 2
    factors = []
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            factors.append(i)
    if n > 1:
        factors.append(n)
    return factors

print(primefactors(600851475143))