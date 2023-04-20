n = int(input())
rods = [int(input()) for i in range(n)]
print(sum(rods)-len(rods)+1)