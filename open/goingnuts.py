ans=0
x=int(input())
while x:
    ans += x%2
    x//=2
print(ans)

