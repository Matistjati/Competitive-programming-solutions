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

ll n;
vi par;
vvi edges;
vector<p2> deepest;

p2 dfs(ll u, ll p) {
    par[u] = p;
    p2 d = { 0, u };
    repe(e, edges[u]) if (e != p) {
        p2 er = dfs(e,u);
        er.first++;
        d = max(d, er);
    }
    return (deepest[u] = d);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;

    par.resize(n);
    edges.resize(n);
    deepest.resize(n);

    rep(i, n - 1)
    {
        ll a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    dfs(0, -1);

    priority_queue<p2> pq;

    vi vis(n);
    vis[0] = 1;

    repe(e, edges[0]) pq.emplace(deepest[e].first, e);

    ll leafs = 0;
    vi ans;
    while (pq.size())
    {
        p2 p = pq.top();
        pq.pop();

        if (vis[p.second]) continue;

        ll u = deepest[p.second].second;
        leafs++;
        while (!vis[u])
        {
            ans.push_back(leafs);
            vis[u] = 1;
            repe(e, edges[u]) pq.emplace(deepest[e].first, e);
            u = par[u];
        }
    }

    repe(a, ans) cout << a << " ";

    return 0;
}
