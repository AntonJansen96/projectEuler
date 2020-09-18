def head(number):
    return sorted(str(number)[0:9]) == ['1','2','3','4','5','6','7','8','9']

def tail(number):
    number %= 10**9
    return sorted(str(number)) == ['1','2','3','4','5','6','7','8','9']

Prev = 0; Next = 1; idx = 1

while (True):
    Next, Prev = Next + Prev, Next
    idx += 1

    if (tail(Next) and head(Next)):
        print(idx)
        break
