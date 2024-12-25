import math
x = int(input())

if x == 1:
    print("0 0")
    exit(0)

ans = (10**100, 10**100)
def invert(k):
    global ans
    lo = -1
    hi = 1
    while math.comb(hi, k) < x:
        hi *= 2
    
    while lo+1<hi:
        mid = (lo+hi)//2
        if math.comb(mid, k) < x:
            lo = mid
        else:
            hi = mid

    if math.comb(hi,k)==x:
        ans = min(ans, (hi,k))

for k in range(1, 200):
    invert(k)
print(*ans)

