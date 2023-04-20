t = int(input())
for i in range(t):
    turtles = [int(j) for j in input().split()]
    imported = 0
    for t in range(1,len(turtles)-1):
        if turtles[t] > turtles[t-1]*2:
            imported += (turtles[t])-(turtles[t-1]*2)
    print(imported)