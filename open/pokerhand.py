a=[i[0] for i in input().split()]
b={}
for i in a:
    if i not in b:
        b[i] = 1
    else:
        b[i] += 1

print(max(b.values()))
