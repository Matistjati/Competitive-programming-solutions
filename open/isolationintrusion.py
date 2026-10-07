n=int(input())
s=[int(input()) for _ in range(3)]
s.sort()
if s[0]+n<s[1]:
    print(min(s)+n)
else:
    print("impossible")
