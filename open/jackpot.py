from math import gcd
t=int(input())
for _ in range(t):
    __=input()
    nums = [int(i) for i in input().split()]
    lcm = 1
    for i in nums:
        lcm = lcm*i//gcd(lcm, i)
    
    if lcm <= int(1e9):
        print(lcm)
    else:
        print("More than a billion.")
