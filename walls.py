l,w,n,r = [int(i) for i in input().split()]

cranes = [tuple(int(j) for j in input().split()) for i in range(n)]

reachable_by = {}

centers = [[-l/2, 0], [l/2,0], [0,-w/2],[0,w/2]]
centers = [tuple(i) for i in centers]

for center in centers:
    for crane in cranes:
        if (center[0]-crane[0])**2+(center[1]-crane[1])**2<=r**2:
            if crane not in reachable_by:
                reachable_by[crane] = set()

            reachable_by[crane].add(center)

completed = set()
chosen_cranes = []

cranes = [i for i in cranes if i in reachable_by]

#print(reachable_by)

best_crane_n = 1e8
for first_crane in cranes:
    partially_complete = set()
    [partially_complete.add(i) for i in reachable_by[first_crane]]
    if len(partially_complete) == 4:
        best_crane_n = 1
        break
    best_temp_n = 0
    best_crane_temp = None

    for second_crane in cranes:
        if len(reachable_by[second_crane].difference(partially_complete)) > best_temp_n:
            best_temp_n = len(reachable_by[second_crane].difference(partially_complete))
            best_crane_temp = second_crane

    if best_crane_temp is None:
        continue

    [partially_complete.add(i) for i in reachable_by[best_crane_temp]]
    if len(partially_complete) == 4:
        if best_crane_n > 2:
            best_crane_n = 2
            continue

    best_temp_n = 0
    best_crane_temp = None

    for second_crane in cranes:
        if len(reachable_by[second_crane].difference(partially_complete)) > best_temp_n:
            best_temp_n = len(reachable_by[second_crane].difference(partially_complete))
            best_crane_temp = second_crane

    if best_crane_temp is None:
        continue

    [partially_complete.add(i) for i in reachable_by[best_crane_temp]]
    if len(partially_complete) == 4:
        if best_crane_n > 3:
            best_crane_n = 3
            continue

    best_temp_n = 0
    best_crane_temp = None

    for second_crane in cranes:
        if len(reachable_by[second_crane].difference(partially_complete)) > best_temp_n:
            best_temp_n = len(reachable_by[second_crane].difference(partially_complete))
            best_crane_temp = second_crane

    if best_crane_temp is None:
        continue

    [partially_complete.add(i) for i in reachable_by[best_crane_temp]]
    if len(partially_complete) == 4:
        if best_crane_n > 4:
            best_crane_n = 4
            continue

if best_crane_n > 100:
    print("impossible")
else:
    print(best_crane_n)

