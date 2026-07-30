#!/usr/bin/python3
from collections import deque
import sys
input = sys.stdin.readline
n,m=map(int,input().split())
adj={}

dummy_index = 0
names = set()
for i in range(m):
    line = input().split()[1:]
    adj[dummy_index] = []
    for name in line:
        if name not in adj:
            adj[name] = []
        names.add(name)
        adj[dummy_index].append(name)
        adj[name].append(dummy_index)
    dummy_index += 1

q = deque()
q.append(("ERDOS",0))

dist = {}
while q:
    node, d = q.popleft()
    if node in dist:
        continue
    dist[node] = d
    for e in adj[node]:
        q.append((e,d+1))

for name in sorted(names):
    assert name in dist
    print(name, dist[name]//2)
