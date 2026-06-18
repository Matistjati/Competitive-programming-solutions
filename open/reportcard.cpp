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

    int n;
    string s;
    cin >> n >> s;
    vi a = {40,40,37,33,30,27,23,20,17,13,10,7,0,0,0};
    vi b = {40,40,40,30,30,30,20,20,20,10,10,10,0,0,0};
    vi delta;
    rep(i,sz(a)) delta.push_back(b[i]-a[i]);
    rep(i,sz(a)) assert(abs(delta[i])<=3);
    // rep(i,sz(delta)) {
    //     cout << delta[i] << ' ';
    // }
    // cout << '\n';

    int dsz = 5*n+10;
    vi dp(2*dsz);
    dp[dsz]=1;
    const ll mod = 1e9+7;

    vi nextdp(sz(dp));
    rep(i,n) {
        fill(all(nextdp),0);
        char c = s[i];
        if (c=='F') continue;
        int base = (c-'A')*3;
        // cerr << "base=" << base << " " << (base-'A') << '\n';

        rep(j,sz(nextdp)) {
            rep(k,3) {
                int val = delta[base+k];
                if (j+val>=0&&j+val<sz(dp)) nextdp[j+val] += dp[j];
            }
        }
        rep(i,sz(nextdp)) nextdp[i]%=mod;
        // rep(i,sz(nextdp)) {
        //     cout << nextdp[i] << ' ';
        // }
        // cout << '\n';
        dp=nextdp;
    }
    ll ans = 0;
    rep(i,dsz) ans += dp[i];
    cout << ans%mod << '\n';


    return 0;
}
