#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    int r, c;
    cin >> r >> c;
    vvi grid(r, vi(c));

    rep(i, r)
    {
        string row;
        cin >> row;
        rep(j, c) grid[i][j] = row[j] - '0';
    }

    queue<pair<int,p2>> q;
    q.emplace(0, p2(0,0));
    vvi vis(r, vi(c));
    vector<p2> dirs = { {0,1},{1,0},{-1,0},{0,-1} };
    while (sz(q))
    {
        int d;
        p2 p;
        tie(d, p) = q.front();
        q.pop();

        if (vis[p.first][p.second]) continue;
        vis[p.first][p.second] = 1;

        if (p.first==r-1&&p.second==c-1)
        {
            cout << d;
            return 0;
        }

        int k = grid[p.first][p.second];
        repe(dir, dirs)
        {
            p2 np = p2(p.first + dir.first * k, p.second + dir.second * k);
            if (np.first < 0 || np.second < 0 || np.first >= r || np.second >= c) continue;
            q.emplace(d + 1, np);
        }
    }

    cout << -1;

    return 0;
}
