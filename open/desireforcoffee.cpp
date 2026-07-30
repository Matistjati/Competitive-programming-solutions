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

using p3 = tuple<ll,ll,ll>;
using vp3 = vector<p3>;

ll best(ll i, ll c, vp3& tstats, ll p, vvi& dp)
{
    if (c < 0)
    {
        return -inf;
    }
    if (i == tstats.size())
    {
        return 0;
    }

    ll k = (c != inf ? c : 501);
    ll& v = dp[i][k];
    if (v != -1) return v;
    ll ret = 0;
    ll cap, wei, prof;
    tie(cap, wei, prof) = tstats[i];

    ret = max(ret, prof + best(i + 1, min(c - wei, cap), tstats, p + prof, dp));
    ret = max(ret, best(i + 1, c, tstats, p, dp));

    return v = ret;
}

ll solveorder(vp3& turtles)
{
    ll n = turtles.size();
    const ll f1 = 1;
    const ll f2 = 0;
    sort(all(turtles), [](p3& a, p3& b)
        {
            return (get<f1>(a) + get<f2>(a)) > (get<f1>(b) + get<f2>(b));
        });

    vvi dp(n, vi(502, -1));
    return best(0, inf, turtles, 0, dp);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    vp3 turtles(n);
    rep(i, n)
    {
        ll cap, wei, prof;
        cin >> cap >> wei >> prof;
        turtles[i] = { cap,wei,prof };
    }

    ll best = 0;
    best = max(best, solveorder(turtles));
    cout << best;

    return 0;
}
