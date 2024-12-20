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
//#include <cassert>
#define assert(x) if (!(x)) __debugbreak()
#endif

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    vvi grid(n, vi(m));
    rep(i, n) rep(j, m) cin >> grid[i][j];

    vector<vector<vi>> cheapeastrots(n, vector<vi>(m));

    auto mincostrot = [&](vi& arr, int k)
        {
            vi cost(sz(arr)/2);
            int s = 0;
            rep(i, k) s += arr[i];
            rep(i, m)
            {
                cost[i] = s;
                s -= arr[i];
                s += arr[i + k];
            }

            vi ret;
            repe(u, cost) ret.push_back(u);
            repe(u, cost) ret.push_back(u);
            return ret;
        };

    rep(i, n)
    {
        vi row = grid[i];
        vi circ;
        rep(i, m) circ.push_back(row[i]);
        rep(i, m) circ.push_back(row[i]);

        rep(j, m)
        {
            vi slice = mincostrot(circ, j+1);
            vi sufmin(sz(slice));
            sufmin.back() = slice.back()+(sz(slice)-1)*k;
            for (int ind = sz(slice)-2; ind >= 0; ind--)
            {
                sufmin[ind] = min(slice[ind]+ ind *k, sufmin[ind + 1]);
            }
            cheapeastrots[i][j] = sufmin;
        }
    }

    priority_queue<pair<int, p2>> pq;
    pq.emplace(0, p2(-1, 0));

    vvi dist(n, vi(m, inf));

    auto relax = [&](p2 p, int cost)
        {
            dist[p.first][p.second] = min(dist[p.first][p.second], cost);
        };
    rep(i, m)
    {
        int cost = cheapeastrots[0][i][0];
        relax(p2(0, i), cost);
    }

    
    rep(i,n-1) rep(j,m)
    {
        p2 p = p2(i,j);

        int d = dist[i][j];


        relax(p2(p.first + 1, p.second), d + grid[p.first + 1][p.second]);

        repp(i, p.second, m)
        {
            int diff = abs(p.second - i);
            int cost = cheapeastrots[p.first + 1][diff][p.second] - k * p.second;
            int nc = d + cost;
            relax(p2(p.first + 1, i), nc);
        }
    }
    cout << dist.back().back() << "\n";
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
