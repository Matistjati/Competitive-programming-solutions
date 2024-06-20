n=int(input())
c=[]
for i in range(2,n):
    s = 0
    while s < n:
        s += i
        if s >= n:
            break
        s += (i - 1)

    if s == n:
        c.append(f"{i},{i-1}")

    s = 0
    while s < n:
        s += i
        if s >= n:
            break
        s += i

    if s == n:
        c.append(f"{i},{i}")

print(f"{n}:")
for i in c:
    print(i)
