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

int dp[1<<14];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    memset(dp,0,sizeof(dp));

    int k,n;
    cin >> k >> n;

    vi top;
    vvi mat(k, vi(n));
    rep(i,k) {
        vector<p2> row(n);
        rep(j,n) cin >> row[j].first, mat[i][j]=row[j].first, row[j].second=j;
        sort(all(row));
        reverse(all(row));
        rep(j,min(n,k)) {
            top.push_back(row[j].second);
        }
    }
    sort(all(top));
    top.erase(unique(all(top)),top.end());
    
    for (auto ind : top) {
        for (int mask = (1<<k)-1; mask; mask--) {
            rep(who,k) {
                int submask = mask & ~(1<<who);
                if (submask == mask) continue;
                dp[mask] = max<int>(dp[mask], dp[submask] + mat[who][ind]);
            }
        }
    }

    cout << dp[(1<<k)-1] << '\n';
    
    return 0;
}
