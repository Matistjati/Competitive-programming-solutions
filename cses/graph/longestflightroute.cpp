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

void dfs(int u, vi& order, vi& vis, vvi& edges)
{
    if (vis[u]) return;
    vis[u] = 1;
    repe(e, edges[u]) dfs(e, order, vis, edges);
    order.push_back(u);
}

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;
    vvi edges(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[a].push_back(b);
    }

    vi vis(n);
    vi order;
    rep(i, n) dfs(i, order, vis, edges);
    reverse(all(order));
    vi dp(n, -inf);
    vi par(n, -2);
    dp[0] = 1;
    repe(u, order)
    {
        repe(e, edges[u])
        {
            if (dp[u]+1>dp[e])
            {
                dp[e] = dp[u] + 1;
                par[e] = u;
            }
        }
    }
    if (dp.back()<0)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }
    int curr = n - 1;
    vi path;
    while (curr !=-2)
    {
        path.push_back(curr);
        curr = par[curr];
    }
    reverse(all(path));
    cout << sz(path) << "\n";
    repe(u, path) cout << u+1 << " ";

    return 0;
}
