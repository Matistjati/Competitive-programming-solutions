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

ll bfs(ll start, ll goal, vector<vector<p2>>& edges) {
    priority_queue<pair<ll, ll>> pq;
    vi vis(edges.size());
    pq.emplace(0, start);

    while (pq.size())
    {
        ll d, u;
        tie(d, u) = pq.top();
        pq.pop();

        if (vis[u]) continue;
        vis[u] = 1;

        if (u == goal) return -d;

        repe(e, edges[u]) pq.emplace(d - e.second, e.first);
    }
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;

    vvi stairs(28);
    vector<vector<p2>> edges(n);

    vi floor(n);

    rep(i, n)
    {
        cin >> floor[i];
        string stair;
        cin >> stair;
        repe(s, stair) stairs[s - 'A'].push_back(i);
    }

    repe(con, stairs)
    {
        rep(i, con.size())
        {
            rep(j, con.size())
            {
                ll a = con[i];
                ll b = con[j];
                ll d = abs(floor[a] - floor[b]);
                edges[a].emplace_back(b, d);
                edges[b].emplace_back(a, d);
            }
        }
    }

    ll ans = 0;
    rep(i, n - 1)
    {
        ans += bfs(i, i + 1, edges);
    }

    cout << ans << '\n';
    return 0;
}
