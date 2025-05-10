p,h,t=map(int,input().split())
if p >= h:
    print(max(0,(t-h)//p))
else:
    print(max(0,(t-p)//h))

