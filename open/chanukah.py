n=int(input())
for i in range(n):
    a,b=[int(i) for i in input().split(" ")]
    print(a,int(b+(b*b+b)/2))

