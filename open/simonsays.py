n=int(input())
for i in range(n):
    o = input()
    if "Simon says" in o:
        print(o.split("Simon says ")[1])
