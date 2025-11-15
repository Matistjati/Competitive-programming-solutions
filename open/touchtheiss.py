#!/usr/bin/python3
p,a=map(int,input().split())
h,s,u=map(int,input().split())

H=s*h
layers_needed = (a+H-1)//H

people_needed = 0
num_pillars = 1
for i in range(layers_needed):
    people_needed += s * num_pillars
    if people_needed > p:
        break
    num_pillars *= u

if people_needed <= p:
    print(people_needed)
else:
    print('no')
