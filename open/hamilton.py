import random

n=int(input())

cache = {}
def ask(a,b):
    if (a,b) not in cache and (b,a) not in cache:
        print(f"? {a+1} {b+1}", flush=True)
        cache[(a,b)] = int(input())
        cache[(b,a)] = 1 - cache[(a,b)]
    return cache[(a,b)]

dp = [10000000] * (max(3,n + 1))
dp[0] = dp[1] = 1
prev_j = [1000000] * (n + 1)
for i in range(3, n+1):
    best = 100000000000
    best_j = -1

    for j in range(2, i):
        cost = dp[j] + (i - j) * (i + j - 1).bit_length()
        if cost < best:
            best = cost
            best_j = j

    assert best_j != -1
    prev_j[i] = best_j
    dp[i] = best

def get_sizes(n):
    if n <= 2:
        return [n]
    j = prev_j[n]
    return get_sizes(j) + [n - j]

def solve(p):
    if len(p) <= 1:
        return p
    
    def insert(path, x):
        l, r = 0, len(path)
        while l < r:
            m = (l + r) // 2
            if ask(path[m], x) == 1:
                l = m + 1
            else:
                r = m
        path.insert(l, x)

    if len(p) % 2 == 1:
        res = solve(p[:-1])
        insert(res, p[-1])
        return res

    is_winner = [0] * len(p)
    for i in range(0,len(p),2):
        is_winner[i] = ask(p[i], p[i+1])
        is_winner[i+1] = 1 - is_winner[i]

    winners = [p[i] for i in range(len(p)) if is_winner[i] == 1]
    winner_path = solve(winners)
    free_mate = p[p.index(winner_path[-1]) ^ 1]
    winner_path.append(free_mate)

    to_merge = []
    for i in range(len(winner_path)-3, -1, -1):
        my_mate = p[p.index(winner_path[i]) ^ 1]
        to_merge.append((winner_path[i], my_mate))

    group_sizes = get_sizes(len(to_merge))
    g_ind = 0
    while len(to_merge) > 0:
        group = to_merge[:group_sizes[g_ind]]
        to_merge = to_merge[group_sizes[g_ind]:]
        g_ind += 1
        for (me, my_mate) in group[::-1]:
            i = winner_path.index(me)
            l, r = i, len(winner_path)
            while l < r:
                m = (l + r) // 2
                if ask(winner_path[m], my_mate) == 1:
                    l = m + 1
                else:
                    r = m
            winner_path.insert(l, my_mate)

    return winner_path

perm = list(range(n))
random.shuffle(perm)


print("!", *(x + 1 for x in solve(perm)))
