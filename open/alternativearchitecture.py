import math
a,b=map(int,input().split())

ans = 0
a-=1
b-=1
a,b=min(a,b),max(a,b)
for x in range(a):
    if a*a < x*x:
        break
    k=a*a-x*x
    if abs(math.sqrt(k)-round(math.sqrt(k)))>1e-9:
        continue
    k=int(math.sqrt(k))
    if b*k % a != 0:
        continue
    if b*x % a != 0:
        continue
    ans += 1

if a != b:
    ans*=2
print(ans)
