import sys
import math

n = int(input())
for i in range(n):
    a, b, op, c, d = [i for i in input().split()]
    a, b, c, d = [int(i) for i in [a, b, c, d]]
    if a < 0 and b < 0:
        a *= -1
        b *= -1
    if c < 0 and d < 0:
        c *= -1
        d *= -1

    if op == '+':
        c *= b
        a *= d
        b *= d
        a += c
    elif op == '-':
        c *= b
        a *= d
        b *= d
        a -= c
    elif op == '*':
        a *= c
        b *= d
    elif op == '/':
        a *= d
        b *= c

    a = int(a)
    b = int(b)
    lc = math.gcd(a, b)
    a //= lc
    b //= lc

    if b < 0:
        a *= -1
        b *= -1

    print(a, "/", b)
