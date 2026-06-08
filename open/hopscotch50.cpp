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

    int n,k;
    cin >> n >> k;

    vvi mat(n,vi(n));
    rep(i,n) rep(j,n) cin >> mat[i][j];
    vector<vector<p2>> locs(k+1);

    map<p2, int> dp;
    rep(i,n) rep(j,n) locs[mat[i][j]].emplace_back(i,j);
    repe(l, locs[1]) dp[l]=0;

    repp(v,1,k+1) {
        map<p2,int> newdp;
        repe(l, locs[v]) {
            if (!newdp.count(l)) newdp[l]=1e9;
            for (auto [p,c] : dp) {
                newdp[l]=min<ll>(newdp[l], abs(l.first-p.first)+abs(l.second-p.second)+c);
            }
        }
        dp = newdp;
    }

    int ans = INT_MAX;
    for (auto [_, c] : dp) ans = min(ans,c);
    if (ans >= 1e9) ans = -1;
    cout << ans << '\n';

    return 0;
}
