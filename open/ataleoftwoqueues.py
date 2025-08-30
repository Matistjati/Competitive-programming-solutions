input()
a=sum(map(int,input().split()))
b=sum(map(int,input().split()))
if a<b:
    print("left")
elif a>b:
    print("right")
else:
    print("either")

