n=int(input())
nums=list(map(int,input().split()))

t=sum(nums)
if t>0:
    print("INFINITY")
elif t<0:
    print("-INFINITY")
else:
    pref = nums
    for i in range(1,n):
        pref[i]+=pref[i-1]
    print(sum(pref)/n)

