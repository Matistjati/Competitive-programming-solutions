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


array<int, 20> best(int u, int p, vvi & adj, vi & dmg)
{
    vector<array<int, 20>> children;

    repe(e, adj[u])
    {
        if (e == p) continue;
        children.push_back(best(e, u, adj, dmg));
    }

    vector<array<int, 20>> dp(sz(children));

    rep(i, sz(children))
    {
        vi prefmin(20, inf);
        vi sufmin(20, inf);
        int m = inf;
        rep(j, 20)
        {
            m = min(m, children[i][j]);
            prefmin[j] = m;
        }
        m = inf;
        for (int j = 19; j >= 0; j--)
        {
            m = min(m, children[i][j]);
            sufmin[j] = m;
        }

        rep(j, 20)
        {
            int m = inf;
            if (j) m = min(m, prefmin[j - 1]);
            if (j < 19) m = min(m, sufmin[j + 1]);
            if (i) dp[i][j] += dp[i-1][j];
            dp[i][j] += m;
        }
    }

    array<int, 20> ret;
    rep(i, 20)
    {
        ret[i] = (i + 1) * dmg[u] + (sz(dp) ? dp.back()[i] : 0);
    }

    return ret;
}

void solve()
{
    int n;
    cin >> n;
    vi dmg(n);
    rep(i, n) cin >> dmg[i];

    vvi adj(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }


    auto ans = best(0, 0, adj, dmg);
    cout << *min_element(all(ans)) << "\n";

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
