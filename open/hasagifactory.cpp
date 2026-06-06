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

    ll w, n;
    cin >> w >> n;

    vector<p2> dp(w + 1, p2(inf, inf));
    dp[0] = { 0,0 };

    rep(i, n) {
        ll x;
        cin >> x;

        vector<p2> newdp(w + 1, p2(inf, inf));

        rep(j, sz(dp)) {
            ll b1 = j;
            ll b2 = dp[j].second;
            ll cost = dp[j].first;
            if (b1 + x <= w) {
                newdp[b1 + x] = min(newdp[b1 + x], p2(cost, b2));
            }
            else {
                newdp[x] = min(newdp[x], p2(cost + 1, b2));
            }

            if (b2 + x <= w) {
                newdp[b1] = min(newdp[b1], p2(cost, b2 + x));
            }
            else {
                newdp[b1] = min(newdp[b1], p2(cost + 1, x));
            }
        }

        dp = newdp;
    }
    repp(i, 1, sz(dp)) dp[i].first++;
    rep(i, sz(dp)) if (dp[i].second > 0) dp[i].first++;
    ll ans = inf;
    rep(i, sz(dp)) ans = min(ans, dp[i].first);
    cout << ans << '\n';

    return 0;
}
