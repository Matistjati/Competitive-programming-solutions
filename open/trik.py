a=1
m=input()
for i in m:
    if i == "A":
        if a == 1:
            a = 2
        elif a == 2:
            a = 1
    elif i == "B":
        if a == 2:
            a = 3
        elif a == 3:
            a = 2
    elif i == "C":
        if a == 1:
            a = 3
        elif a == 3:
            a = 1
print(a)
