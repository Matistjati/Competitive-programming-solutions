#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }


signed main()
{
    fast();

    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    repe(row, grid) cin >> row;

    p2 p, a;
    rep(i, r) rep(j, c)
    {
        if (grid[i][j] == 'P') p = { i,j };
        if (grid[i][j] == 'A') a = { i,j };
    }

    vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
    queue<p2> q;
    vvi dist(r, vi(c, inf));
    vector<vector<p2>> par(r, vector<p2>(c, p2(-1,-1)));
    q.emplace(p);
    dist[p.first][p.second] = 0;

    while (sz(q))
    {
        p2 po = q.front();
        q.pop();
        
        repe(dir, dirs)
        {
            p2 np = p2(po.first + dir.first, po.second + dir.second);
            if (grid[np.first][np.second] == '#') continue;
            if (dist[po.first][po.second]+1<dist[np.first][np.second])
            {
                dist[np.first][np.second] = dist[po.first][po.second] + 1;
                par[np.first][np.second] = po;
                q.emplace(np);
            }
        }
    }

    if (dist[a.first][a.second]==inf)
    {
        cout << "call for help";
    }
    else
    {
        vector<p2> path;
        while (a.first!=-1)
        {
            path.push_back(a);
            a = par[a.first][a.second];
        }
        path.erase(path.begin());
        path.pop_back();
        repe(p, path) grid[p.first][p.second] = 'X';
        repe(row, grid) cout << row << "\n";
    }

    return 0;
}
