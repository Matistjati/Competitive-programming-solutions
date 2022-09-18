import sys
import math

q = int(input())
for i in range(q):
    ans = 1
    n = int(input())
    ans = math.comb(2*n,n)//(n+1)

    print(ans)
