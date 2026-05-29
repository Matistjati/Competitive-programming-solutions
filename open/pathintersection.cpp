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

const int maxn = 2e5;
int up[19][maxn];
int tin[maxn], tout[maxn], depth[maxn];
int timer = 0;
void dfs(int u, int p, vvi& adj) {
    depth[u] = depth[p] + 1;
    tin[u] = timer++;
    up[0][u] = p;
    repp(d, 1, 19) {
        up[d][u] = up[d - 1][up[d - 1][u]];
    }

    repe(e, adj[u]) if (e != p) dfs(e, u, adj);

    tout[u] = timer++;
}

int isancestor(int a, int b) {
    return tin[a] <= tin[b] && tin[b] <= tout[a];
}

int lca(int a, int b) {
    if (isancestor(a, b)) return a;
    if (isancestor(b, a)) return b;
    for (int d = 18; d >= 0; d--) {
        if (!isancestor(up[d][a], b)) {
            a = up[d][a];
        }
    }
    return up[0][a];
}

int dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;
    vvi adj(n);
    rep(i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    depth[0] = -1;
    dfs(0, 0, adj);

    auto on_path = [&](int a, int b, int c) {
        if (isancestor(a, b) || isancestor(b, a)) {
            if (!isancestor(a, b)) swap(a, b);
            return isancestor(a, c) && isancestor(c, b);
        }
        int lc = lca(a, b);
        return (isancestor(c, a) || isancestor(c, b)) && isancestor(lc, c);
    };

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--; b--; c--; d--;


        vi lcas;
        int ab_lca = lca(a, b);
        for (auto u : { a,b }) {
            for (auto v : { c,d }) {
                int lc = lca(u, v);
                if (on_path(a, b, lc) && on_path(c,d,lc)) {
                    lcas.push_back(lc);
                }
            }
        }
        if (lcas.empty()) {
            cout << "-1\n";
        }
        else if (sz(lcas) == 1) {
            cout << lcas[0] + 1 << ' ' << lcas[0] + 1 << '\n';
        }
        else {
            int score = -1;
            p2 best;
            repe(a, lcas) repe(b, lcas) {
                int d = dist(a, b);
                if (d > score) {
                    score = d;
                    best = { a,b };
                }
            }
            cout << best.first + 1 << ' ' << best.second + 1 << '\n';
        }
    }

    return 0;
}
