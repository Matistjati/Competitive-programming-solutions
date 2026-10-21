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
    
    int t;
    cin >> t;
    mt19937 rng(42);
    while (t--) {
        int n;
        cin >> n;
        vector<int> wts(n);
        rep(i,n) cin >> wts[i];
        shuffle(all(wts),rng);

        using bset = bitset<81*300>;
        int window = 20;
        vector<bset> dp(2*window);
        dp[window][0]=1;

        for (int w : wts) {
            vector<bset> newdp(2*window);

            rep(i,2*window) {
                if (i) newdp[i-1] |= dp[i];
                if (i+1<2*window) newdp[i+1] |= dp[i] << w;
            }

            dp = newdp;
        }

        int tot = accumulate(all(wts), 0);
        p2 ans = {tot,tot};
        repp(d,-1,2) {
            int p1 = window-d;
            rep(i,sz(dp[p1])) if (dp[p1][i]) ans = min(ans, p2(max(i, tot-i),i));
        }
        int w2 = tot-ans.second;
        cout << min<int>(w2,ans.second) << " " << max<int>(w2,ans.second) << '\n';
    }
    
    return 0;
}
