n = int(input())
for i in range(n):
    a,b,c = [int(i) for i in input().split()]
    d = a - b
    if a < b-c:
        print("advertise")
    elif a > b-c:
        print("do not advertise")
    else:
        print("does not matter")
