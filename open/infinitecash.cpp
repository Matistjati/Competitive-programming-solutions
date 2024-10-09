import sys
s,d,m = int(input(),2),int(input(),2),int(input(),2)

def b(x):
    return bin(x)[2:]

for i in range(1010):
    for j in range(d):
        #print(j,s)
        if m==0:
            print(b(i*d+j))
            sys.exit(0)
        m = m//2

    m+=s
print("Infinite money!")

