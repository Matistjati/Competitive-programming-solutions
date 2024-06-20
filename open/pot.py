a = int(input())
s=0
for i in range(a):
    o = input()
    s+=pow(int(o[:-1]),int(o[-1]))
print(s)
