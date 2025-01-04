import subprocess as s
n=int(input());x=n*(n+1)//2;o={1:0};a=1
if x!=1:
    for i in map(int,s.run(["factor",str(x)],capture_output=1).stdout.decode().split(": ")[1].split()):o[i]=o.get(i,0)+1
for c in o.values():a*=(c+1)
print(a)
