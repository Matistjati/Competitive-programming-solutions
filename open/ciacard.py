def bonus(x):
    if x <= 1999:
        return 0
    if x<=3999:
        return 25
    if x<=5999:
        return 50
    if x<=7999:
        return 75
    return 150

x=int(input())
if x >=8000*2:
    print(300)
    exit(0)

ans=0
for a in range(x+1):
    for b in range(x+1):
        if a+b!=x:
            continue
        ans=max(ans,bonus(a)+bonus(b))
print(ans)

