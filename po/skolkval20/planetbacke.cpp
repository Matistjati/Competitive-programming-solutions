n,m=[int(i) for i in input().split()]
grid = [[ord(c)-ord('0') for c in input()] for i in range(n)]

memo = {}

dirs = ((0,1),(1,0),(0,-1),(-1,0),(1,1),(-1,1),(1,-1),(-1,-1))
def best(r, c, vis):
    if (r,c,vis) in memo:
        return memo[(r,c,vis)]
    h = grid[r][c]

    ret = 0
    for dir in dirs:
        nr = r + dir[0]
        nc = c + dir[1]

        if nr < 0 or nc < 0 or nr >= n or nc >= m or grid[nr][nc]>h:
            continue

        ind = nr*m+nc
        if grid[nr][nc]==h:
            if vis & (1<<ind):
                continue
            newvis = vis | (1<<ind)
        else:
            newvis = 1<<ind
        ret = max(ret, 1+best(nr,nc,newvis))
    memo[(r,c,vis)] = ret
    return ret

ans = 0
for i in range(n):
    for j in range(m):
        ans = max(ans, best(i,j,1<<(i*m+j)))
print(ans+1)
