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

vvi queries;
vi ans;


void dfs(int u, int p, int d, ll tot, ll dtot, vi& done, vvi& adj) {
    repe(q, queries[u]) {
        tot += q+1;
        dtot--;
        done[min(sz(adj), d+q+1)]++;
    }
    dtot += done[d];
    tot += dtot;
    ans[u] = tot;

    repe(e, adj[u]) {
        if (e == p) continue;

        dfs(e, u, d + 1, tot, dtot, done, adj);
    }
    repe(q, queries[u]) {
        done[min(sz(adj), d+q+1)]--;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vvi adj(n);
    rep(i, n - 1) {
        int p;
        cin >> p;
        p--;
        adj[i + 1].push_back(p);
        adj[p].push_back(i + 1);
    }

    queries.resize(n);
    ans.resize(n);
    rep(i, q) {
        int a, b;
        cin >> a >> b;
        queries[a - 1].push_back(b);
    }

    vi done_at(n+1);
    dfs(0, 0, 0, 0, 0, done_at, adj);

    rep(i, n) cout << ans[i] << ' ';
    cout << '\n';

    return 0;
}
