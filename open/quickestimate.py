import math
n=int(input())
for i in range(n):
    o = float(input())
    if o == 0.:
        print(1)
    else:
        print(math.ceil(math.log(o)/math.log(10)+0.00001))
