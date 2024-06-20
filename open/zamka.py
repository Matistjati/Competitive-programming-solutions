def sum_digits(n):
    s = 0
    while n:
        s += n % 10
        n //= 10
    return s
l = int(input())
d = int(input())
x = int(input())

n = 0
m = 0
for i in range(l,d+1):
    if sum_digits(i) == x:
        n = i
        break

for i in range(d,l-1, -1):
    if sum_digits(i) == x:
        m = i
        break
print(n)
print(m)

