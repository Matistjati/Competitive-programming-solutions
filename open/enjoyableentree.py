fib=[(1,0),(0,1)]


while len(fib) < 10**6:
    p1 = fib[-1]
    p2 = fib[-2]
    tot = sum(p1)+sum(p2)
    x=(p1[0]+p2[0], p1[1]+p2[1])
    x = (x[0]/tot,x[1]/tot)

    fib.append(x)

n = int(input())
n-=1
if n < len(fib):
    print(*(x*100 for x in fib[n]))
else:
    print(*(x*100 for x in fib[-1]))
