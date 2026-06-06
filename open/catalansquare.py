
fac = [1]
for i in range(1,10004):
    fac.append(fac[-1]*i)

n=int(input())

ind = n+1
print(fac[ind*2]//fac[ind]//fac[ind]//(ind+1))