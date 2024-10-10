t=int(input())
d=-1
c=-1
a=[]
b=[]
seen = {}
def f(x,y):
    
    if x > 0 and y > 0:
        if ((x,y)) in seen:
            return seen[(x,y)]
        ret = c
        for A,B in zip(a,b):
            ret += f(x-A,y-B)
        seen[(x,y)]=ret
        return ret
    else:
        return d

for _ in range(t):
    seen = {}
    while len(a):
        del a[-1]
    while len(b):
        del b[-1]
    l = [int(i) for i in input().split()]
    d=l[-1]
    del l[-1]
    c=l[-1]
    del l[-1]
    for i in range(0,len(l),2):
        a.append(l[i])
    for i in range(1,len(l),2):
        b.append(l[i])
    queries = [int(i) for i in input().split()]
    for i in range(0,len(queries),2):
        print(f(queries[i],queries[i+1]))
    print("")
