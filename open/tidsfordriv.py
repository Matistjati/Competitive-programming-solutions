#!/usr/bin/python3
n = int(input())

seen = {}
for i in range(n):
    card = input()[:-1]
    if card not in seen:
        seen[card]=0
    seen[card]+=1

if len(seen)<13:
    print(4/(52-n))
else:
    print((4-min(seen.values()))/(52-n))
