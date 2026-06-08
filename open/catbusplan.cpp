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

struct UF {
    vi par;
    UF(int n) : par(n) { iota(all(par), 0); }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b) {
        a = find(a); b = find(b);
        par[b] = a;
    }
};

void dfs(int u, vi& vis, vector<vector<p2>>& adj, vector<p2>& order) {
    while (sz(adj[u])) {
        auto [e, i] = adj[u].back();
        adj[u].pop_back();
        if (vis[i]) continue;
        vis[i] = 1;
        dfs(e, vis, adj, order);
        order.emplace_back(i, u);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;

    UF uf(n);
    vi deg(n);
    vector<vector<p2>> adj(n);
    vector<p2> edges(m);
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        deg[a]++;
        deg[b]++;
        uf.merge(a, b);
        edges[i] = { a,b };
        adj[a].emplace_back(b, i);
        adj[b].emplace_back(a, i);
    }

    map<int, vi> odd;
    rep(i, n) {
        if (deg[i] % 2 == 1) odd[uf.find(i)].push_back(i);
    }

    int extra = 0;
    for (auto [_, odds] : odd) {
        assert(sz(odds) % 2 == 0);

        for (int i = 0; i < sz(odds) - 2; i += 2) {
            edges.emplace_back(odds[i], odds[i + 1]);
            adj[odds[i]].emplace_back(odds[i + 1], m + extra);
            adj[odds[i + 1]].emplace_back(odds[i], m + extra);
            extra++;
        }
    }

    vi vis(sz(edges));
    vvi paths;

    auto start_dfs = [&](int u) {
        vector<p2> order;
        dfs(u, vis, adj, order);
        if (order.empty()) return;
        // order is euler tour of this component
        vi curr;
        p2 last;
        reverse(all(order));
        rep(j, sz(order)) {
            curr.push_back(order[j].second);
            last = order[j];
            if (order[j].first >= m) {
                if (sz(curr)) {
                    paths.push_back(curr);
                }
                curr = {};
            }
        }
        if (sz(curr)) {
            auto [u, v] = edges[last.first];
            curr.push_back(u == curr.back() ? v : u);
            paths.push_back(curr);
        }
    };

    for (auto [_, odds] : odd) {
        if (sz(odds)) start_dfs(odds.back());
    }

    rep(i, n) {
        start_dfs(i);
    }

    if (sz(paths) > k) {
        cout << "Impossible\n";
        return 0;
    }
    if (m < k) {
        cout << "Impossible\n";
        return 0;
    }

    rep(i, sz(paths)) {
        if (sz(paths) == k) break;

        while (sz(paths[i]) > 2 && sz(paths) < k) {
            int ei = paths[i].back();
            paths[i].pop_back();
            paths.push_back({ paths[i].back(), ei });
        }
    }

    cout << "Possible\n";
    assert(sz(paths) == k);
    rep(i, k) {
        repe(u, paths[i]) {
            cout << u + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}
