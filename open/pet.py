m=0
mi=-1
for i in range(5):
    o =sum([int(i) for i in input().split()])
    if o > m:
        m = o
        mi = i +1
print(mi,m)
