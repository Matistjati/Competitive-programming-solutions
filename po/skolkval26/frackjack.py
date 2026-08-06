#!/usr/bin/python3
a=int(input())
b=int(input())
a_dist = 21 - a
b_dist = 21 - b
if a_dist < 0:
    a_dist = 1e9
if b_dist < 0:
    b_dist = 1e9

if a_dist == b_dist:
    print("Jack")
elif a_dist < b_dist:
    print("Alice")
else:
    print("Bertil")
