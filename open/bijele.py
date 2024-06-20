h=[1,1,2,2,2,8]
a=[h[i]-int(n) for i,n in enumerate(input().split())]
for i in a:
    print(str(i)+" ",end="")
