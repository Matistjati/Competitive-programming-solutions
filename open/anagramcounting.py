import sys
import math

for line in sys.stdin:
    a=line.strip()
    freq={}
    for i in a:
        if i not in freq:
            freq[i]=0
        freq[i]+=1

    ans = math.factorial(len(a))

    for i in freq:
        #print(i)
        ans = ans // math.factorial(freq[i])

    print(int(ans))
