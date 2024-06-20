prev=""
hiss = False
for i in input():
    if prev == i and prev == "s":
        print("hiss")
        hiss = True
        break
    prev = i
if not hiss:
    print("no hiss")
