#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define int ll
#define rep(i,hi) for (int i = 0; i < (hi); i++)

const int inf = int(1e14);

vector<string> grid;
int r,c;
int dp[1<<11][101][11];
int best(int i, int j, int mask, int cost)
{
    if (i==-1) return 0;
    if (j==c) return best(i-2,0,mask,cost);
    assert(j<c);
    assert(i>=0);
    assert(mask < (1<<c));

    int& v = dp[mask][i][j];
    if (v!=-1) return v;

    bool anycan = grid[i][j] == '#' || grid[i-1][j] == '#';

    if (j==c-1)
    {
        if (anycan) return v = inf;
        else
        {
            return v = best(i-2, 0, mask & ~(1<<j), cost);
        }
    }
    bool possible = (mask & (1<<j)) > 0;
    possible |= (mask & (1<<(j+1))) > 0;

    int ret = inf;
    if (anycan)
    {
        if (!possible) return v = inf;
        else
        {
            ret = min(ret, 1+best(i, j+2, mask | (1<<j) | (1<<(j+1)),cost+1));
        }
    }
    else
    {
        ret = min(ret, best(i,j+1, mask & ~(1<<j), cost));
        if (possible) ret = min(ret, 1+best(i, j+2, mask | (1<<j) | (1<<(j+1)), cost+1));
    }
    
    return v=ret;
}

signed main()
{
    memset(dp, -1, sizeof(dp));
    cin >> r >> c;
    grid.resize(r);

    rep(i,r) cin >> grid[i];

    cout << best(r-1, 0, (1<<c)-1, 0);

}
