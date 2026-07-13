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

    ll n, l;
    cin >> n >> l;

    vector<vector<p2>> toendstation(n);
    vector<vector<p2>> fromendstation(n);

    rep(i, l)
    {
        ll m;
        cin >> m;

        vector<ll> stations(m);
        for (auto& v : stations) cin >> v;
        rep(i, m) stations[i]--;

        repp(i, 1, m)
        {
            fromendstation[stations[0]].emplace_back(stations[i], i);
            toendstation[stations[i]].emplace_back(stations[0], m - 1 - i);
        }

        rep(i, m - 1)
        {
            fromendstation[stations.back()].emplace_back(stations[i], m - 1 - i);
            toendstation[stations[i]].emplace_back(stations.back(), i);
        }

    }

    priority_queue<tuple<ll,ll,ll>> q;
    q.emplace(0, 0, 0);
    vvi vis(n, vi(2));

    while (q.size())
    {
        ll d, u, isend;
        tie(d, u, isend) = q.top();
        q.pop();

        if (vis[u][isend]) continue;
        vis[u][isend] = 1;

        if (u == n - 1)
        {
            cout << -d;
            return 0;
        }

        if (isend)
        {
            repe(e, fromendstation[u]) q.emplace(d - e.second, e.first, 0);
        }
        repe(e, toendstation[u]) q.emplace(d - e.second, e.first, 1);

    }

    return 0;
}
