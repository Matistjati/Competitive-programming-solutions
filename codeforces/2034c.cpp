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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


void solve()
{
    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    rep(i, r) cin >> grid[i];
    map<char, p2> dirs;
    dirs['U'] = p2(-1, 0);
    dirs['D'] = p2(1, 0);
    dirs['L'] = p2(0, -1);
    dirs['R'] = p2(0, 1);

    int cc = r * c;
    vector<vector<p2>> redges(cc);
    vector<vector<p2>> edges(cc);
    auto h = [&](int a, int b)
        {
            return a * c + b;
        };
    auto h2 = [&](p2 x)
        {
            return x.first * c + x.second;
        };
    auto outside = [&](p2 s)
        {
            return s.first < 0 || s.second < 0 || s.first >= r || s.second >= c;
        };

    queue<p2> q2;
    queue<p2> q;
    rep(i, r) rep(j, c)
    {
        if (grid[i][j]=='?')
        {
            continue;
        }
        p2 d = dirs[grid[i][j]];
        p2 np = p2(i + d.first, j + d.second);
        if (outside(np))
        {
            q.emplace(p2(i,j));
        }
        else
        {
            q2.emplace(p2(i, j));
            redges[h2(np)].push_back(p2(i, j));
        }
    }

    vvi removed(r,vi(c));
    while (sz(q))
    {
        p2 p = q.front();
        q.pop();

        removed[p.first][p.second] = 1;
        repe(e, redges[h2(p)])
        {
            q.emplace(e);
        }
    }
    int ans = 0;

    rep(i, r) rep(j, c)
    {
        if (removed[i][j]) continue;
        int any = 0;
        repe(dir, dirs)
        {
            p2 np = p2(i + dir.second.first, j + dir.second.second);
            if (outside(np))
            {
                continue;
            }
            if (!removed[np.first][np.second])
            {
                any++;
            }
        }
        ans += any > 0;
    }

    cout << ans << "\n";
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }


    return 0;
}
