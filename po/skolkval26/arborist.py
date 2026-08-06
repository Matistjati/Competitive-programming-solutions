#!/usr/bin/python3
n,k=map(int,input().split())

coords = list(map(int,input().split()))
weights = list(map(int,input().split()))

time = 2*n

while coords:
    curr_weight = 0
    max_coord = -1
    while 1:
        best_index = -1
        best_coordinate = -1
        for i in range(len(coords)):
            if weights[i]+curr_weight <= k and coords[i] > best_coordinate:
                    best_coordinate = coords[i]
                    best_index = i
        if best_index == -1:
            break
        max_coord = max(max_coord, coords[best_index])
        curr_weight += weights[best_index]
        coords.pop(best_index)
        weights.pop(best_index)
    assert max_coord != -1
    time += 2*max_coord

print(time)
