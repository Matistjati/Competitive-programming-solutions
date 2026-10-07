r,c,n=map(int,input().split())
if r*c % n != 0:
    print("impossible")
    exit(0)

amount = r*c//n

import math
s1 = math.gcd(c,amount)
s2 = amount//s1
res=[['?'] * c for i in range(r)]
clen = c // s1
rlen = s2
lettergroup = [chr(ord('A')+i) for i in range(clen)]
placed=0
for i in range(r):
    for j in range(c):
        res[i][j]=lettergroup[j//(c//clen)]
    placed+=1
    if placed==rlen:
        lettergroup = [chr(ord('A')+j+(1+(i//rlen))*clen) for j in range(clen)]
        placed=0

for i in range(r):
    print("".join(res[i]))
