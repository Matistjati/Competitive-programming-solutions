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

char dp[21][21][51][51], nextdp[21][21][51][51];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    memset(dp, 0xff, 21*21*51*51);
    memset(nextdp, 0xff, 21*21*51*51);

    int n,a,b,c;
    cin >> n >> a >> b >> c;

    const int smallinf = 1e9;

    dp[0][0][c][b]=0;
    int ans = smallinf;
    rep(i,smallinf) {
        if (i>=ans) break;

        // are we done?
        rep(budget_loss, n+1) rep(budget_loss_tomorrow,n+1) {
            if (dp[budget_loss][budget_loss_tomorrow][0][0] >= a) ans=min<int>(ans,i+2);
            if (dp[budget_loss][0][0][0] >= a) ans=min<int>(ans,i+1);
            if (dp[0][0][0][0] >= a) ans=min<int>(ans,i);
        }

        // transitions
        rep(left_b, b+1) rep(left_c, c+1) rep(budget_loss, n+1) rep(budget_loss_tomorrow,n+1) {
            char got_small = dp[budget_loss][budget_loss_tomorrow][left_c][left_b];
            if (got_small<0) continue;

            int budget = n-budget_loss;
            int budget_tomorrow = n-budget_loss_tomorrow;
            rep(g3, left_c+1) {
                if (g3 * 3 > min<int>(budget, budget_tomorrow)) break;
                rep(g2, left_b+1) {
                    if (g3 * 3 + g2 * 2 > min<int>(budget,budget_tomorrow)) break;
                    char spare = budget - g3*3 - g2*2;
                    char& v = nextdp[g3*3+g2*2+budget_loss_tomorrow][g3*3][left_c-g3][left_b-g2];
                    v = max<char>(v, got_small + spare);
                }
            }
        }
        swap(dp,nextdp);
    }
    cout << ans << '\n';

    return 0;
}
