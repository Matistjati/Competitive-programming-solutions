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

const int MAX_SUM = 1000*100;
using bset = bitset<MAX_SUM>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n;
    cin >> n;
    bset dp;
    dp[0]=1;
    int t = 0;
    rep(i,n) {
        int x;
        cin >> x;
        t+=x;
        dp |= dp << x;
    }

    if (t%2==0 && dp[t/2]) cout << "YES\n";
    else cout << "NO\n";
    
    return 0;
}
