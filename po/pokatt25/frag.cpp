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


struct SlopeTrick {
    ll total_slope_change = 0; // total slope change from breakpoints
    ll k = 0, m = 0; // leftmost line
    map<ll, ll> breakpoints;
    void add(const SlopeTrick& other) {
        k += other.k;
        m += other.m;
        total_slope_change += other.total_slope_change;
        for (auto [x, dk] : other.breakpoints) {
            breakpoints[x] += dk;
        }
    }
    void prefixmin() {
        while (sz(breakpoints) && k + total_slope_change > 0) {
            auto it = prev(end(breakpoints));
            if (k + total_slope_change - it->second > 0) {
                total_slope_change -= it->second;
                breakpoints.erase(it); // can safely remove
            }
            else {
                // remove only partially
                ll remove_amount = k + total_slope_change;
                it->second -= remove_amount;
                total_slope_change -= remove_amount;
            }
        }
    }
    ll eval(ll x) {
        if (breakpoints.empty()) return k * x + m;
        ll cur_slope = k;
        ll cur_x = begin(breakpoints)->first;
        ll cur_y = m + cur_slope * cur_x;
        for (auto [b, dk] : breakpoints) {
            if (x < b) {
                return cur_y + cur_slope * (x - cur_x);
            }
            cur_y += cur_slope * (b - cur_x);
            cur_slope += dk;
            cur_x = b;
        }
        return cur_y + cur_slope * (x - cur_x);
    }
};

SlopeTrick rat_line(ll energy, ll free_stalling)
{
    SlopeTrick ret;
    ret.k = 0;
    ret.m = 0;
    ret.breakpoints[free_stalling] = energy;
    ret.total_slope_change = energy;
    return ret;
}

int n;
vector<vector<p2>> adj;
vi has_rat, energy_cost;
SlopeTrick dfs(int u, int p, ll free_stalling)
{
    SlopeTrick ret;
    if (has_rat[u] == 1)
    {
        ret = rat_line(energy_cost[u], free_stalling);
    }
    else
    {
        for (auto [e, d] : adj[u])
        {
            if (e == p) continue;
            SlopeTrick c = dfs(e, u, free_stalling + d);
            if (sz(ret.breakpoints) < sz(c.breakpoints)) swap(ret, c);
            ret.add(c);
        }
        if (u != 0)
        {
            ret.k -= energy_cost[u];
            ret.prefixmin();
            ret.k += energy_cost[u];
        }
    }

    return ret;
}

int main()
{
    int n, m, t;
    cin >> n >> m >> t;
    adj.resize(n);
    has_rat.resize(n);
    energy_cost.resize(n);

    rep(i, n - 1)
    {
        int a, b, d;
        cin >> a >> b >> d;
        adj[a].emplace_back(b, d);
        adj[b].emplace_back(a, d);
    }

    for (int i = 1; i < n; i++) cin >> energy_cost[i];

    rep(i, m)
    {
        int x;
        cin >> x;
        has_rat[x] = 1;
    }

    auto ans = dfs(0, 0, 0);
    cout << ans.eval(t) << '\n';

    return 0;
}
