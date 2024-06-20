s = 0
n = int(input())
for i in range(n):
    a = [float(i) for i in input().split(" ")]
    s += a[0]*a[1]
print(s)
