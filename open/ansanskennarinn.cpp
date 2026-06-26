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
    assert(nums[0]!=nums[1]);

    vi delta(n-1);
    rep(i,n-1) delta[i]=abs(nums[i+1]-nums[i]);
    ll g = delta[0];
    rep(i,n-1) g = gcd(g,delta[i]);

    bool neg = false;
    rep(i,n) {
        if (nums[i]!=nums[0]) {
            neg = nums[i]<nums[0];
            break;
        }
    }
    ll dir = (neg?-g:g);
    cout << dir << '\n';
    sort(all(nums));
    ll x = nums[0];
    ll i = 0;
    while (i>=0 && i<n) {
        if (nums[i]!=x) {
            cout << x << '\n';
        }
        else i++;
        x+=abs(dir);
    }

    return 0;
}
