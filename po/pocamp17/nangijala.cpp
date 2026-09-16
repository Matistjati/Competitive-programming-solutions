#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())


int dfs(int u, vi& vis, vvi& edges)
{
    if (vis[u]) return 0;
    vis[u] = 1;
    int ret = 1;
    repe(e, edges[u]) ret += dfs(e, vis, edges);
    return ret;
}
int dp[10][int(1e5 + 10)];
int best(int u, int p, int pc, vvi& edges)
{
    int& v = dp[pc][u];
    if (v != -1) return v;
    int ret = 1e9;
    rep(c, 10) {
        if (c == pc) continue;
        int k = c;
        repe(e, edges[u]) if (e != p) k += best(e, u, c, edges);
        ret = min(ret, k);
    }

    return v = ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n,m;
    cin >> n >> m;
    vvi adj(n);
    rep(i, m) {
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int maxdeg = 0;
    rep(i, n) maxdeg = max<int>(maxdeg, sz(adj[i]));

    int ans = 0;
    if (maxdeg <= 2)
    {
        vi vis(n);
        rep(i, n) { // lines
            if (sz(adj[i]) == 1) {
                ans += dfs(i, vis, adj) / 2;
            }
        }

        rep(i, n) { // cycles 
            if (vis[i]) continue;
            int k = dfs(i, vis, adj);
            if (k == 1) continue;
            assert(k > 2);
            if (k % 2 == 1) ans += (k - 1) / 2 + 2;
            else ans += k / 2;
        }
    }
    else {
        memset(dp, -1, sizeof(dp));
        ans = best(0, 0, 9, adj);
    }

    cout << ans;
    
    return 0;
}
