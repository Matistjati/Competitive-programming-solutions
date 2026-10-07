#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;
#define rep(i,n) for (ll i = 0; i < (n); i++)
using vi = vector<ll>;
using p2 = pair<ll,ll>;
#define sz(x) ((ll)x.size())
#define all(x) begin(x),end(x)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n,m,k;
    cin >> n >> m >> k;
    vector<vector<p2>> adj(n);
    vi wts;
    rep(i,m) {
        ll a,b,w;
        cin >> a >> b >> w;
        adj[a].emplace_back(b,w);
        wts.emplace_back(w);
    }

    {
        queue<p2> q;
        q.emplace(0,0);
        vi vis(n);
        while (sz(q)) {
            auto [d,u] = q.front();
            q.pop();
            if (vis[u]) continue;
            vis[u]=1;

            if (u==n-1) {
                if (d<=k) {
                    cout << "0\n";
                    return 0;
                }
                break;
            }

            for (auto [e,w] : adj[u]) {
                q.emplace(d+1,e);
            }
        }
    }

    sort(all(wts));
    wts.erase(unique(all(wts)),end(wts));
    // now WLOG our path will have length >= k
    ll ans = inf;
    for (auto tw : wts) {
        priority_queue<p2> pq;
        pq.emplace(0, 0);
        vi dist(n, inf);
        dist[0]=0;

        while (sz(pq)) {
            auto [d,u] = pq.top();
            pq.pop();
            d=-d;

            if (d>dist[u]) continue;
            if (u==n-1) {
                ans = min(ans, d-k*tw);
                break;
            }
            for (auto [e,w] : adj[u]) {
                w = max(0LL, w-tw) + tw;
                if (w+d < dist[e]) {
                    dist[e]=w+d;
                    pq.emplace(-(w+d),e);
                }
            }
        }
    }
    cout << ans << '\n';

    return 0;
}
