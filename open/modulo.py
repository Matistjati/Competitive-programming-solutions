s=set()
for i in range(10):
    a = int(input())%42
    if a not in s:
        s.add(a)
print(len(s))
