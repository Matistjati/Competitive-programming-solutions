input()
s=0
for i in [int(i) for i in input().split(" ")]:
    if i < 0:
        s+=1
print(s)


