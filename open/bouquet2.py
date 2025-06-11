#!/usr/bin/python3
import math

n = int(input())
flowers = []
colors = []

for i in range(n):
    line = input().split()
    ind = 0
    if line[2]=='G':
        ind=1
    if line[2]=='R':
        ind=2
    colors.append(ind)
    flowers.append((int(line[0]),int(line[1])))

def dist(a, b):
    d1 = a[0]-b[0]
    d2 = a[1]-b[1]
    return math.sqrt(d1*d1+d2*d2)

origin = (0,0)
inf = 100000000000000
ans = inf
for i in range(n):
    best = [inf] * 3

    for j in range(n):
        if colors[j]==colors[i]:
            continue
        d = dist(origin, flowers[j])+dist(flowers[j],flowers[i])
        best[colors[j]] = min(best[colors[j]], d)
    t = 0
    for j in range(3):
        if j==colors[i]:
            continue
        t+=best[j]
    ans = min(ans, t)

print(ans)

