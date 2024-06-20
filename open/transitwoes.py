s,t,n=[int(i) for i in input().split()]
time = [int(i) for i in input().split()]
buslength = [int(i) for i in input().split()]
arrivals = [int(i) for i in input().split()]
s+= time[0]
time = time[1:]


currPoint = 0
for i in range(n):
    if s < arrivals[i]:
        s+=buslength[i]+time[i]
        currPoint += 1

if currPoint == n-1:
    print("yes")
else:
    print("no")
