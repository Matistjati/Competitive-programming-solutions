#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
const ll inf = 1e18;

int n,m;
ll dp[int(5e5+10)];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    rep(i,n+2) dp[i]=inf;

    dp[0] = 0;
    rep(i,n) {
        ll cost = dp[i];
        ll buy_cost;
        cin >> buy_cost;
        cost += buy_cost;

        repp(days,1,m+1) {
            if (i+days>n) continue;
            ll c;
            cin >> c;
            dp[i+days]=min(dp[i+days],cost-c);
        }
    }
    cout << dp[n] << '\n';
    return 0;

}
