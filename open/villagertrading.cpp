#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll,ll>;
const ll inf = 1e18;

#define repe(i, arr) for (auto& i : arr)
#define rep(i, b) for(ll i = 0; i < (b); ++i)
#define repp(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)x.size())

using ld = long double;

void dfs(ll u, vi& vis, vvi& edges) {
    if (vis[u]) return;
    vis[u] = 1;
    repe(e, edges[u]) dfs(e, vis, edges);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    map<string, ll> itemind;

    vector<vector<pair<ll, ld>>> edges;
    vector<tuple<ll, ll, ld>> edgelist;
    vvi redges;
    rep(i, n) {
        ll m;
        cin >> m;
        rep(i, m) {
            int va, vb;
            string na,nb;
            cin >> va >> na >> vb >> nb;

            if (!itemind.count(na)) itemind[na] = itemind.size();
            if (!itemind.count(nb)) itemind[nb] = itemind.size();
            int ia = itemind[na];
            int ib = itemind[nb];

            while (edges.size() <= max(ia, ib)) edges.push_back(vector<pair<ll, ld>>()), redges.push_back(vi());
            ld w = -logl((vb + 0.0) / va);
            edges[ia].emplace_back(ib, w);
            edgelist.emplace_back(ia, ib, w);
            redges[ib].emplace_back(ia);
        }
    }

    n = itemind.size();
    vi seesemerald(n);
    if (!itemind.count("Emerald")) {
        cout << "no";
        return 0;
    }
    dfs(itemind["Emerald"], seesemerald, redges);

    bool ans = 0;
    vi vis(n);

    vector<ld> dist(n, 0);

    rep(j, n) { // Phases of relaxation
        for (auto [a,b,w] : edgelist) {
            if (dist[a] + w < dist[b]) {
                dist[b] = dist[a] + w;
                if (j == n - 1 && seesemerald[b]) ans = 1;
            }
        }
    }

    cout << (ans ? "yes" : "no");

    return 0;
}
