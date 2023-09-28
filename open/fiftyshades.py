n = int(input())
s = 0
for i in range(n):
    a = input()
    if "rose" in a.lower() or "pink" in a.lower():
        s += 1

if s > 0:
    print(s)
else:
    print("I must watch Star Wars with my daughter")
