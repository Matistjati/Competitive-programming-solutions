from operator import mul

a=int(input())

while len(str(a)) > 1:
    coef = [int(i) for i in str(a)]
    o = 1
    for i in coef:
        o *= i if i != 0 else 1
    
    a = o

print(a)
