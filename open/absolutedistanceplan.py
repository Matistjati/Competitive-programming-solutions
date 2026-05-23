# Probably overcomplicated...
import sys
n=int(input())
import random

def ask(p):
    print(f"?", *p)
    return int(input())

def get_delta(a,b):
    g = [0] * n
    v=2
    for j in range(n):
        if j not in (a,b):
            g[j]=v
            v+=1
    g[a] = 1
    g[b] = n

    v1 = ask(g)
    g[a] = n
    g[b] = 1

    v2 = ask(g)
    return v1-v2

def solve_subset(pivots):
    deltas = []
    for i in range(len(pivots)):
        deltas.append(get_delta(pivots[i],pivots[(i+1)%len(pivots)]))
    # assume s[0]=t
    relative_t = [0]
    for i in range(len(pivots)-1):
        relative_t.append(-deltas[i]//2+relative_t[-1])
    m = min(relative_t)
    corr = 1-m
    relative_t = [i + corr for i in relative_t]
    return relative_t

if n<=1200:
    # Solve all in 2N
    print("!", *solve_subset(list(range(n))))
    exit(0)
else:
    k=80
    k2=40
    pivots = random.sample(list(range(n)), k)

    # Phase 1: find out the exact value of *some* number
    relative_t = solve_subset(pivots)

    best = (10**18, 0)

    for delta in range(n-max(relative_t)):
        g = [0] * n
        
        unused = list(sorted(list(set(range(1,n+1))-set(i+delta for i in relative_t)), reverse=True))

        for i in range(len(pivots)):
            g[pivots[i]] = relative_t[i]+delta
        
        for i in range(n):
            if i not in pivots:
                g[i] = unused[-1]
                del unused[-1]
        res = ask(g)
        best = min(best, (res, delta))
    
    relative_t = [i+best[1] for i in relative_t]

    ans = [-1] * n
    for i in range(len(pivots)):
        ans[pivots[i]]=relative_t[i]

    left = []
    for i in range(n):
        if i not in pivots:
            left.append(i)
    random.shuffle(left)

    # We have found the value of some number!
    pivot = max(pivots, key=lambda x: relative_t[pivots.index(x)])
    u = relative_t[pivots.index(pivot)]

    # Phase 2: find all values >= k2
    big = []
    small = []
    while len(left):
        size_before = len(left)

        cands = left[:k2]
        left = left[k2:]
        base = [0] * n
        
        unused = list(sorted(list(set(range(1,n+1))-set([n])), reverse=True))
        base[pivot] = n
        
        for i in range(len(cands)):
            base[cands[i]] = unused[-1]
            del unused[-1]

        for i in range(n):
            if base[i]==0:
                base[i]=unused[-1]
                del unused[-1]

        base_cost = ask(base)
        pivot = max(pivots, key=lambda x: relative_t[pivots.index(x)])

        num_questionmark = 0
        for i in cands:
            if i in pivots:
                continue
            base[i], base[pivot] = base[pivot], base[i]
            cost_2 = ask(base)
            base[i], base[pivot] = base[pivot], base[i]

            bi = base[i]
            bp = base[pivot]
            xp = u

            delta = cost_2 - base_cost

            target_val = delta - abs(xp - bi) + abs(xp - bp)

            if abs(target_val) == abs(bp - bi):
                num_questionmark+=1
                if target_val != bp-bi:
                    big.append(i)
                else:
                    small.append(i)
            else:
                if bi < bp:
                    ans[i] = (bp + bi - target_val) // 2
                else:
                    ans[i] = (target_val + bp + bi) // 2

    # Phase 3: handle all <= k2
    left = small
    ans[big[0]] = n
    relative_here = solve_subset(left)
    m = 1-min(relative_here)
    relative_here = [i+m for i in relative_here]

    seen = [0] * (n+1)
    for i in range(n):
        if ans[i]!=-1:
            seen[ans[i]]=1

    for delta in range(n):
        good = True
        for i,l in enumerate(left):
            v=relative_here[i]
            if delta+v<1 or delta+v > n or seen[delta+v]:
                good = False
                break
        if not good:
            continue

        for i,l in enumerate(left):
            v=relative_here[i]
            ans[l] = v

    print("!", *ans)
    exit(0)
