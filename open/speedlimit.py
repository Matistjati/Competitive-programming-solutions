while True:
    n = int(input())
    if n == -1:
        break

    s = 0
    prev = 0
    for i in range(n):
        a,b=[int(i) for i in input().split()]
        s += a*(b-prev)
        prev=b
        
    print(f"{s} miles")
