a,b=[int(i) for i in input().split()]
d=(b-45)
if d < 0 or d % 60 == 0:
    a-=1


if a < 0:
    a+=24
    




print(a, d%60)
