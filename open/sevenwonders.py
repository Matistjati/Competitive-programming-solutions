o={"T":0,"C":0,"G":0}
for i in input():
    o[i]+=1

s=0
s+=o["T"]*o["T"]
s+=o["C"]*o["C"]
s+=o["G"]*o["G"]
while True:
    if abs(o["T"]*o["C"]*o["G"]) > 0:
        s+=7
    else:
        break

    o["T"]-=1
    o["C"]-=1
    o["G"]-=1
    

print(s)
