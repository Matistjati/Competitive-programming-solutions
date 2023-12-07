n=int(input())
v=[int(i) for i in input().split()]
for i in range(n):
    v[i] = (v[i],i)
v = sorted(v,reverse=True)

t = 0
for i in range(1,n):
    t+=v[i][0]

if v[0][0]>t:
    print("impossible")
else:
    [print(i[1]+1,end=" ") for i in v]