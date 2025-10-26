d=input()
ans=int(d.split('+')[1])
d=d.split('+')[0]
v=int(d.split('d')[1])
ans+=int(d.split('d')[0])*((v+1)/2)
print(ans)

