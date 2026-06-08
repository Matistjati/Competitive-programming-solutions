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

using bset = bitset<int(5e7)>;
bset dp;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    if (n>=25) {
        cout << "0\n";
        return 0;
    }

    vector<int> nums(n);
    rep(i,n) cin >> nums[i];

    
    dp[sz(dp)/2]=1;

    mt19937 rng(42);
    shuffle(all(nums),rng);
    repe(x,nums) {
        if (dp[sz(dp)/2+x]) {
            cout << "0\n";
            return 0;
        }
        dp |= (dp<<x) | (dp>>x);
    }

    int ans = 30;

    repp(i,1,sz(dp)/2) if (dp[i+sz(dp)/2]) ans = min(ans,popcount((unsigned)i));

    cout << ans << '\n';

    return 0;
}
