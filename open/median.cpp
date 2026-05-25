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
    cin >> n;
    vi nums(n);
    rep(i,n) cin >> nums[i];
    sort(all(nums));

    if (n%2==0) cout << fixed << setprecision(15) << (nums[n/2]+nums[n/2-1])/2.0 << '\n';
    else cout << nums[n/2] << '\n';

    return 0;
}
