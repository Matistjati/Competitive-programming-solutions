n,t = [int(i) for i in input().split()]
a = [int(i) for i in input().split()]

if t == 1:
    print(7)
elif t == 2:
    if a[0] > a[1]:
        print("Bigger")
    elif a[0] == a[1]:
        print("Equal")
    else:
        print("Smaller")
elif t == 3:
    a=sorted(a[:3])
    print(a[1])
elif t == 4:
    print(sum(a))
elif t == 5:
    print(sum([i for i in a if i % 2 == 0]))
elif t == 6:
    a = [i % 26 for i in a]
    a = [chr(i+97) for i in a]
    print("".join(a))
elif t == 7:
    i = 0
    n = 0
    while True:
        i = a[i]
        if i > len(a)-1 or i < 0:
            print("Out")
            break
        elif i == len(a)-1:
            print("Done")
            break
        if n > len(a)*10:
            print("Cyclic")
            break
        n+=1
