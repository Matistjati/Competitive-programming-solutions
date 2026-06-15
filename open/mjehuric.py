arr=[int(i) for i in input().split()]

def sorted(arr):
    for i in range(4):
        if arr[i]>arr[i+1]:
            return False
    return True

while not sorted(arr):
    for i in range(4):
        if arr[i]>arr[i+1]:
            arr[i],arr[i+1]=arr[i+1],arr[i]
            print(*arr)

