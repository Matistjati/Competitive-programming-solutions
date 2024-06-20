n,b=input().split()
n=int(n)*4
s = 0
yd = {"A":11,"K":4,"Q":3,"J":20,"T":10,"9":14,"8":0,"7":0}
nd = {"A":11,"K":4,"Q":3,"J":2,"T":10,"9":0,"8":0,"7":0}
for i in range(n):
    a = input()
    s += (yd if a[1] == b else nd)[a[0]]

print(s)

