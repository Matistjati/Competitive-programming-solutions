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

    p2 s, g;
    rep(i, r) rep(j, c)
    {
        if (grid[i][j] == 'S') s = p2(i, j);
    }

    queue<pair<int,p2>> q;
    q.emplace(0, s);
    vvi vis(r, vi(c));
    vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
    while (sz(q))
    {
        auto [d, p] = q.front();
        q.pop();
        if (vis[p.first][p.second]) continue;
        vis[p.first][p.second] = 1;
        if (grid[p.first][p.second]=='G')
        {
            cout << d << "\n";
            return 0;
        }
        repe(dir, dirs)
        {
            p2 np = p2(p.first + dir.first, p.second + dir.second);
            if (np.first < 0 || np.second < 0 || np.first >= r || np.second >= c || grid[np.first][np.second] == '#') continue;
            q.emplace(d + 1, np);
        }
    }
    cout << "thralatlega nettengdur";

    return 0;
}
