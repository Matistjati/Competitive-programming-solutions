n,o = map(int,input().split())

p = []
for i in range(n-1):
  p.append(-1)

for i in range(n-1):
  p[(i+int(n/2-1)+o-1)%(n-1)] = i+1

p.insert(int(n/2-1),n)

left = p[int(n/2):]
right = p[:int(n/2)]
right.reverse()

for i in range(int(n/2)):
  print(f"{left[i]}-{right[i]}")
