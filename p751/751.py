#!/usr/bin/env python3

def generator(b1: float):
    b_prev = b1  # b1
    yield int(b_prev)  # a1
    while True:
        b_next = int(b_prev) * (b_prev - int(b_prev) + 1)
        a_next = int(b_next)
        b_prev = b_next
        yield a_next

theta = 2.22356101931355410617317719226235906

gen = generator(theta)
number = ""
for idx in range(len(str(theta))):
    if idx == 0:
        number += str(next(gen)) + '.'
    else:
        number += str(next(gen))

print(number)
print(number[0:24])

# 2.223561019313554106173177
# Just manually adjusting :-)
