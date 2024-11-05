#FUCK this input format
from heapq import heappush, heappop
t=int(input())
input()
for _ in range(t):
    f,n=[int(i) for i in input().split()]
    is_firestation = [0 for i in range(n)]
    for i in range(f):
        s = int(input())
        s-=1
        is_firestation[s]=1
    
    edges = [[] for i in range(n)]
    try:
        while l:=input().strip():
            if l=="\n":
                break
            a,b,c=[int(i) for i in l.split()]
            a-=1
            b-=1
            edges[a].append((b,c))
            edges[b].append((a,c))
    except Exception:
        pass
    ans = (1000000000000, 0)
    for s in range(n):
        if is_firestation[s]:
            continue
        pq = []
        dist = [100000000000 for i in range(n)]
        for i in range(n):
            if is_firestation[i]:
                dist[i]=0
                heappush(pq, (0, i))
        dist[s]=0
        heappush(pq, (0, s))
        while len(pq):
            d,u=heappop(pq)
            if d>dist[u]:
                continue
            for e in edges[u]:
                nd = d+e[1]
                if nd<dist[e[0]]:
                    dist[e[0]] = nd
                    heappush(pq, (nd, e[0]))
        if max(dist) < ans[0]:
            ans = (max(dist), s)
    print(ans[1]+1)
