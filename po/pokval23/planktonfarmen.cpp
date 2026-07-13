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

    ll a, n;
    cin >> a >> n;
    multiset<ll> nums;
    rep(i, n)
    {
        ll num;
        cin >> num;
        nums.insert(num);
    }

    ll ans = 0;
    while (nums.size())
    {
        auto it = nums.begin();
        ll v = *it;
        nums.erase(it);

        ll smallest = (a+v-1) / v;

        auto b = nums.lower_bound(smallest);
        if (b != end(nums))
        {
            ans++;
            nums.erase(b);
        }
    }
    cout << ans << '\n';

    return 0;
}
