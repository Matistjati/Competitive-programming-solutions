x1,y1=[int(i) for i in input().split()]
x2,y2=[int(i) for i in input().split()]
x3,y3=[int(i) for i in input().split()]
x = -1
y = -1
if(x1==x2):
    x = x3
elif x1==x3:
    x = x2
else:
    x = x1

if(y1==y2):
    y = y3
elif y1==y3:
    y = y2
else:
    y = y1

print(f"{x} {y}")
