import math
while True:
    a,b,c=[float(i) for i in input().split()]
    if a==0 and b==0 and c==0:
        break
    est = c/b*a*a*4
    if est-math.floor(est) < 0.000001:
        est = int(est)
    print(a*a*3.14159265358979, est)
