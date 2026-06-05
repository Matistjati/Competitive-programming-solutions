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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,m,d;
    cin >> n >> m >> d;
    d--;

    vector<vector<pair<ll,ll>>> adj(n);
    rep(i,m) {
        ll a,b,w;
        cin >> a >> b >> w;
        a--; b--;
        adj[b].emplace_back(a,w);
    }

    priority_queue<pair<ll,int>,vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    vi dist(n,inf), par(n,-2);
    par[d]=d;
    dist[d]=0;
    pq.emplace(0,d);
    while (sz(pq)) {
        auto [d,u] = pq.top();
        pq.pop();
        if (d>dist[u]) continue;
        for (auto [e, w] : adj[u]) {
            if (d+w<dist[e] || (d+w==dist[e] && u<par[e])) {
                dist[e]=d+w;
                par[e]=u;
                pq.emplace(d+w,e);
            }
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        x--;
        cout << par[x]+1 << '\n';
    }

    return 0;
}
