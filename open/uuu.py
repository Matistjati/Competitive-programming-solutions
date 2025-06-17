#!/usr/bin/env python3

import random

n, m = [int(i) for i in input().split()]


def find(i, ans=[0]):
    while parent[i] != i:
        ans[0] += 1
        i = parent[i]
    return i


def depth(i):
    d = 0
    while parent[i] != i:
        d += 1
        i = parent[i]
    return d


def union(i, j):
    i = find(i)
    j = find(j)
    if size[i] < size[j]:
        (i, j) = (j, i)
    size[i] += size[j]
    parent[j] = i


def find_worst(i):
    p = find(i)
    bestI = -1
    bestScore = -1
    for j in range(n):
        ans = [0]
        if find(j) == p and depth(j) > bestScore:
            bestI = j
            bestScore = ans[0]

    return bestI


size = [1] * n
parent = list(range(n))

bois = [[i] for i in range(n)]
added = []

while len(bois) > 1:
    newbois = []

    while len(bois) >= 2:
        a, b = bois.pop(), bois.pop()
        c, d = find_worst(a[-1]), find_worst(b[0])
        added.append((min(c, d), max(c, d)))
        b.extend(a)
        newbois.append(b)
    if len(bois) == 1:
        newbois.append(bois.pop())

    bois = list(reversed(newbois))

answer = 0
for edge in added:
    (u, v) = edge
    u -= 1
    v -= 1
    if find(u) != find(v):
        answer -= 1
    union(u, v)

"""
edges = []
for i in range(n):
    ans = [0]
    k=find(i,ans)
    edges.append([-ans[0],i,k])
    #if ans[0]>bestC:
    #    bestC = ans[0]
    #    best = i
edges = sorted(edges)
#print(edges)
freq = {}
for edge in edges:
    if edge[0] not in freq:
        freq[edge[0]] = 0
    freq[edge[0]] += 1
#print(freq)

def game():
    for i in range(n):
        for j in range(n):
            if i != j and (min(i,j),max(i,j)) not in added:
                added.append((min(i,j),max(i,j)))
                return

#while len(added)<m:
#    game()
"""

ind = []
for i in range(n):
    for j in range(i + 1, n):
        ind.append([-depth(i) - depth(j), i, j])
ind = sorted(ind)

for d, a, b in ind:
    a, b = min(a, b), max(a, b)
    if (a, b) not in added:
        added.append((a, b))
    if len(added) >= m:
        break

if True:
    # print(n,len(added))
    for i in added:
        print(i[0] + 1, i[1] + 1)
