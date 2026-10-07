
import string
alpha = string.ascii_lowercase

qu = []
resp=[]
n=0
for i in range(5):
    q=""
    for j in range(26):
        if (j>>i) % 2 == 0:
            q += alpha[j]
    qu.append(q)
    print("?", q)
    res=list(map(int,input().split()))[1:]
    if res:
        n=max(n,max(res))
    resp.append(set(res))

res = []
for i in range(n):
    cands = set(c for c in alpha)
    for j in range(5):
        if i+1 in resp[j]:
            cands = set(c for c in cands if c in qu[j])
        else:
            cands = set(c for c in cands if c not in qu[j])
    assert len(cands)==1
    res.append(list(cands)[0])
print("!","".join(res))
