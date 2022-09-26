import math


while True:
    n = int(input())
    if n==0: break
    n-=1

    ans = []
    for i in range(65):
        if (n&(1<<i)):
            ans.append(3**i)
    print("{ " + ", ".join(str(i) for i in ans)+" }")
