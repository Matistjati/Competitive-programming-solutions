#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

int dfs(int u, vi& vis, vector<vector<p2>>& adj)
{
    int ret = 0;
    for (auto [e, i] : adj[u])
    {
        if (vis[i]) continue;
        vis[i] = 1;
        ret = max(ret, 1 + dfs(e, vis, adj));
        vis[i] = 0;
    }

    return ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    while (cin >> n >> m && n)
    {
        vector<vector<p2>> adj(n);
        rep(i, m) {
            int a, b;
            cin >> a >> b;
            adj[a].emplace_back(b,i);
            adj[b].emplace_back(a,i);
        }
        int ans = 0;
        vi vis(m);
        rep(i, n) ans = max(ans, dfs(i, vis, adj));
        cout << ans << endl;
    }

    return 0;
}
