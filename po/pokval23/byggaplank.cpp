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
#define per(i, b) for (ll i = (b) - 1; i >= 0; --i)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, k;
    cin >> n >> k;

    vector<ll> heights(n);
    for (auto& v : heights) cin >> v;

    vvi prevSmaller(n, vi(k + 1, -1));
    vvi nextSmaller(n, vi(k + 1, n));

    vi placements_made(n, 0);
    set<p2> activenums;
    rep(i, n)
    {
        auto lo = activenums.upper_bound(p2(heights[i], inf));

        for (auto p = lo; p != activenums.end();)
        {
            p2 curr = *p;

            nextSmaller[curr.second][placements_made[curr.second]] = i;

            placements_made[curr.second]++;
            if (placements_made[curr.second] >= k + 1) p = activenums.erase(p);
            else p++;
        }
        activenums.insert(p2(heights[i], i));
    }

    placements_made = vi(n, 0);
    activenums = set<p2>();
    per(i, n)
    {
        auto lo = activenums.upper_bound(p2(heights[i], inf));

        for (auto p = lo; p != activenums.end();)
        {
            p2 curr = *p;

            prevSmaller[curr.second][placements_made[curr.second]] = i;

            placements_made[curr.second]++;
            if (placements_made[curr.second] >= k + 1) p = activenums.erase(p);
            else p++;
        }
        activenums.insert(p2(heights[i], i));
    }

    vi pref(n);
    pref[0] = heights[0];
    repp(i, 1, n) pref[i] = pref[i - 1] + heights[i];

    ll ans = 0;
    rep(i, n)
    {
        rep(j, k + 1)
        {
            ll sz = (nextSmaller[i][j] - 1) - (prevSmaller[i][k - j] + 1) + 1;
            ans = max(ans, heights[i] * sz);
        }
    }
    cout << ans << '\n';

    return 0;
}
