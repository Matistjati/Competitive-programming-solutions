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

using vp2 = vector<p2>;
using vvp2 = vector<vp2>;
ll fillcities(vp2& cities, vvp2& edges, vi& populations, ll node, ll par) {
    ll ret = 0;

    repe(edge, edges[node])
    {
        if (edge.first == par) continue;
        cities[edge.first].first = edge.second;
        ret += fillcities(cities, edges, populations, edge.first, node);
    }

    ret += populations[node];

    cities[node].second = ret;

    return ret;
}

// Cities: first cost, second value
// For each cost of each node, best is to either take this node or subset of children nodes
void best(vp2& cities, vvp2& edges, vi& dp, ll node, ll par)
{
    vi dp2(dp.size(), 0);

    rep(i, dp.size())
    {
        ll newV = 0;
        if (cities[node].first <= i)
        {
            newV = cities[node].second + dp[i - cities[node].first];
        }

        dp2[i] = max(dp[i], newV);
    }

    repe(edge, edges[node])
    {
        if (edge.first == par) continue;

        best(cities, edges, dp, edge.first, node);
    }

    rep(i, dp.size()) dp[i] = max(dp2[i], dp[i]);

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, b;
    cin >> n >> b;

    vvp2 edges(n);

    vi populations(n);
    rep(i, n - 1) cin >> populations[i + 1];

    rep(i, n - 1)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        edges[a].emplace_back(b, c);
        edges[b].emplace_back(a, c);
    }

    // Cost, value
    vp2 cities(n);
    fillcities(cities, edges, populations, 0, -1);
    cities[0].first = inf;

    vi dp(b + 1);

    best(cities, edges, dp, 0, -1);

    cout << *max_element(all(dp));

    return 0;
}
