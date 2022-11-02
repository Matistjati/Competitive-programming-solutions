import math
import random
import sys

# Lots of special cases, pretty horrid code. The test cases were really generous
n = 0
while True:
    n = int(input())
    if n==-1:
        break

    if n==0:
        print(10)
        continue
    elif n==1:
        print(11)
        continue

    digits = []
    primes = [2,3,5,7]

    twos = []

    while n%2==0:
        twos.append(2)
        n//=2

    while len(twos)>2:
        twos.pop()
        twos.pop()
        twos.pop()
        digits.append(8)


    threes = []
    while n%3==0:
        threes.append(3)
        n//=3

    while len(threes)>1:
        threes.pop()
        threes.pop()
        digits.append(9)
    
    if len(twos):
        if len(twos)==2:
            if len(threes):
                threes.pop()
                digits.append(6)
                digits.append(2)
            else:
                digits.append(4)
        else:
            if len(threes):
                threes.pop()
                digits.append(6)
            else:
                digits.append(2)

    

    if len(threes):
        digits.append(3)

    primes = [5,7]
    for p in primes:
        while n%p==0:
            digits.append(p)
            n//=p

    if n!=1:
        print("There is no such number.")
        continue

    digits = sorted(digits)
    if len(digits)==1:
        digits.insert(0,1)
    print("".join(map(str, digits)))
    
        
