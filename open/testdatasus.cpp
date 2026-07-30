#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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

    int n, cap;
    cin >> n >> cap;
    vector<pair<int,int>> items(n);
    for (auto& [p, w] : items) cin >> p >> w;
    sort(all(items), [&](pair<int,int> a, pair<int,int> b) {
        return (ll)a.first * b.second > (ll)b.first * a.second;
    });

    const int cutoff_lo = 250;
    const int cutoff = 300;
    int center = sqrt(3*n/2);
    int lo = max<int>(0,center-cutoff_lo);
    int hi = min(n, center+cutoff);

    int ans = 0;
    rep(i,lo) {
        ans += items[i].first;
        cap -= items[i].second;
    }

    vector<int> dp(cap+1);
    repp(i,lo,hi) {
        auto [p,w] = items[i];
        #pragma GCC unroll 8
        rep(i,cap+1-w) {
            dp[i] = max(dp[i], dp[i+w]+p);
        }
    }

    cout << ans+dp[0] << '\n';

    return 0;
}
