import math
n = int(input())
for i in range(n):
    v, theta,x,h1,h2=[float(i) for i in input().split()]
    theta*=3.14/180
    t=x/(v*math.cos(theta))
    y = v*t*math.sin(theta)-0.5*9.81*t*t
    if (h2 - y > 1 and y - h1 > 1):
        print("Safe")
    else:
        print("Not Safe")
