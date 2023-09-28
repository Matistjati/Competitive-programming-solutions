import math
n=int(input())
o=[int(i) for i in input().split()]
o = sorted(o, reverse=True)
t=0
i=0
while i < n:
    if i + 2 < n:
        t+=o[i+2]
        i+=3
    else:
        break

print(t)
    
