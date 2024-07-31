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

void topsort(int u, vi& order, vi& vis, vvi& edges)
{
    if (vis[u]) return;
    vis[u] = 1;
    repe(e, edges[u]) topsort(e, order, vis, edges);
    order.push_back(u);
}

const int mod = int(1e9 + 7);
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
    vi order;
    vi vis(n);
    rep(i, n) topsort(i, order, vis, edges);
    reverse(all(order));
    vi dp(n);
    dp[0] = 1;
    repe(u, order)
    {
        repe(e, edges[u])
        {
            dp[e] = (dp[e] + dp[u]) % mod;
        }
    }
    cout << dp.back();

    return 0;
}
