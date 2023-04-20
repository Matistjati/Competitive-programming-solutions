n = int(input())
presses = [int(input()) for i in range(n)]

pressed = False
time = 0
for i in range(len(presses)):
    if pressed:
        time += presses[i] - presses[i-1]

    pressed = not pressed

if pressed:
    print("still running")
else:
    print(time)
