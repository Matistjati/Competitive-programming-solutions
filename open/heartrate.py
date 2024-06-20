n = int(input())
for i in range(n):
    a,b=input().split(" ")
    print(f"{60/(float(b)/(float(a)-1))} {60/(float(b)/(float(a)))} {60/(float(b)/(float(a)+1))}")
