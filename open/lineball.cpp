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

int hopcroftKarp(vector<vi>& g, vi& r) {
        int n = sz(g), res = 0;
        vi l(n, -1), q(n), d(n);
        auto dfs = [&](auto f, int u) -> bool {
                int t = exchange(d[u], 0) + 1;
                for (int v : g[u])
                        if (r[v] == -1 || (d[r[v]] == t && f(f, r[v])))
                                return l[u] = v, r[v] = u, 1;
                return 0;
        };
        for (int t = 0, f = 0;; t = f = 0, d.assign(n, 0)) {
                repp(i,0,n) if (l[i] == -1) q[t++] = i, d[i] = 1;
                repp(i,0,t) for (int v : g[q[i]]) {
                        if (r[v] == -1) f = 1;
                        else if (!d[r[v]]) d[r[v]] = d[q[i]] + 1, q[t++] = r[v];
                }
                if (!f) return res;
                repp(i,0,n) if (l[i] == -1) res += dfs(dfs, i);
        }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,m;
    cin >> n >> m;
    vvi adj(m);
    rep(i,n) {
        int a,b;
        cin >> a >> b;
        // a--; b--;
        adj[a].push_back(b);
    }

    vi r(m,-1);
    cout << hopcroftKarp(adj, r) << '\n';

    return 0;
}
