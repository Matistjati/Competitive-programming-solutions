def rotate(msg, amount):
    return ((msg >> amount) | (msg << (20 - amount))) & 0xfffff

def transform(msg):
    msg = msg & 0xffffffffff
    
    a = msg & 0xfffff
    a = rotate(a, 6)
    a = a ^ 0xc21f3
    a = a | 0xaaaaa

    b = (msg >> 20) & 0xfffff
    b = b ^ a
    b = b | 0xaaaaa
    b = b ^ 0xbf83f
    b = rotate(b, 6)

    a = a ^ b

    return (a << 20) | b
    
t=int(input())
from random import randint
while 1:
    x = randint(0, 2**40-1)
    if transform(x)==t:
        print(x)
        break

