n = int(input())

for i in range(n):
    strips = [int(j) for j in input().split()]
    print(sum(strips)-strips[0]-len(strips)+2)
