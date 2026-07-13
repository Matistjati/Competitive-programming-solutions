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

ll best(ll i, ll left, bool active, vi& won, vector<vvi>& dp) {
    if (i == won.size()) return 0;

    if (dp[i][left][active] != -1) return dp[i][left][active];

    ll ret = 0;
    if (active)
    {
        ret = max(ret, won[i] + best(i + 1, left, true, won, dp)); // keep going
        ret = max(ret, best(i + 1, left, false, won, dp)); // Stop going
    }
    if (!active)
    {
        if (left > 0) ret = max(ret, won[i] + best(i + 1, left - 1, true, won, dp)); // start
        ret = max(ret, best(i + 1, left, false, won, dp)); // dont start
    }

    return (dp[i][left][active] = ret);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vi won(n);
    rep(i, n)
    {
        char r;
        cin >> r;
        won[i] = (r == 'V' ? 1 : -1);
    }

    vector<vvi> dp(n, vvi(k + 1, vi(2, -1)));
    cout << best(0, k, false, won, dp) << '\n';
}
