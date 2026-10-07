s=input()

import itertools

def remap(x):
    if x=='h': return 0
    if x=='d': return 1
    if x=='c': return 2
    if x=='s': return 3
    assert False

nums = [remap(x) for x in s]

ans = 0
for perm in itertools.permutations(range(0,4)):
    dp=[0]*4

    for c in nums:
        value = perm[c]
        v = dp[value]
        for j in range(value, 4):
            dp[j]=max(dp[j],1+v)
    ans=max(ans,max(dp))

print(len(s)-ans)

