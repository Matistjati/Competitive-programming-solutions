import math
k = input()

done = False

f = 1
for i in range(1, 11):
    f*=i
    if str(f)==k:
        print(i)
        done = True

if not done:
    base10Len = 0
    f = 1
    for i in range(1, 100000000):
        base10Len += math.log10(i)
        if math.ceil(base10Len)==len(k):
            print(i)
            break
