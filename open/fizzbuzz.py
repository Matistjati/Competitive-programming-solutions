x,y,n = [int(i) for i in input().split()]

for i in range(1,n+1):
    p = ""
    if i%x==0:
        p+="Fizz"
    if i%y==0:
        p+="Buzz"
    if p == "":
        p = i
    print(p)
