n = int(input())
times = [[int(j) for j in input().split()] for i in range(n)]

topSpeed = -1
for i in range(1,len(times)):
    speed = (times[i][1]-times[i-1][1])/(times[i][0]-times[i-1][0])
    if speed > topSpeed:
        topSpeed = speed

print(int(topSpeed))