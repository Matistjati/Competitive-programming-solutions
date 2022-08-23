import math

a, b, c = [int(i) for i in input().split()]

try:
    k = math.log(math.log(a)) + c * math.log(b)
    k2 = math.log(math.log(a)) + math.log(b) + math.log(c)
    if abs(k - k2) > 0.0001:
        print("Oh look, a squirrel!")
    else:
        print("What an excellent example!")
except:
    if pow(pow(a, b), c) == pow(a, pow(b, c)):

        print("What an excellent example!")
    else:
        print("Oh look, a squirrel!")
