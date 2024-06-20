c = float(input())
l = int(input())
s = 0
for i in range(l):
    a,b=[float(i) for i in input().split()]
    s+=a*b
print(s*c)
