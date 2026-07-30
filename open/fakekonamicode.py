curr_dir = 0
s=input()
D=input()
dir = -1
if D=="north": dir=0
elif D=="west": dir=1
elif D=="south": dir=2
elif D=="east": dir=3
else: assert 0

deltas = [1 if d == '<' else -1 for d in s]

ans = 10**16
last_seen = [-10**16] * 4
last_seen[0] = -1

net = sum(deltas)
if net%4==dir:
    print(0)
else:
    pref = 0
    for i in range(len(deltas)):
        pref += deltas[i]
        # net-pref+pre = dir
        # pre = dir+pref-net
        ans = min(ans, i-last_seen[(dir+pref-net)%4])
        last_seen[pref%4]=i

    if ans > len(deltas):
        print(-1)
    else:
        print(ans)
