n,m=map(int,input().split())

for t in range(1, 10**6+1):
    target = t*m//n

    val = target//m
    res = target%m + 1
    if val<1 or res < 1 or val > 10**6 or res > 10**6:
        continue

    s = val*n+res*(n//m)
    if s>t:
        continue

    x = [val]*n
    j = m-1
    num=0
    while j < n:
        num+=1
        x[j]+=res
        j+=m
    if sum(x)>t:
        continue
    x[-1] += t-sum(x)
    print("YES")
    print(*x)
    exit(0)
print("NO")
