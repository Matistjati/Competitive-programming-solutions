#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;
#define rep(i,n) for (ll i = 0; i < (n); i++)
using vi = vector<ll>;

const int upper = 1002;
short dp[(1<<16)+1][upper];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    rep(i,1<<16) rep(j,upper) dp[i][j]=30000;

    ll n;
    cin >> n;
    vi arr(n);
    rep(i,n) cin >> arr[i];

    dp[0][0]=0;
    rep(mask,1<<n) {
        rep(i,n) {
            if (mask&(1<<i)) continue;
            short w = arr[i];
            auto* ndp = dp[mask | (1<<i)];
            auto* cdp = dp[mask];
            rep(curr_imbalance, upper) {
                {
                    short new_imbalance = min<short>(upper-1,curr_imbalance+w);
                    ndp[new_imbalance] = min(ndp[new_imbalance], max(new_imbalance, cdp[curr_imbalance]));
                }
                {
                    short new_imbalance = min<short>(upper-1,abs(curr_imbalance-w));
                    ndp[new_imbalance] = min(ndp[new_imbalance], max(new_imbalance, cdp[curr_imbalance]));
                }
            }
        }
    }
    ll ans = inf;
    rep(i,upper) ans = min<ll>(ans, dp[(1<<n)-1][i]);
    cout << ans << '\n';

    return 0;
}
