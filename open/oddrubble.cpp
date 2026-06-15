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

    ll n, q;
    cin >> n >> q;

    vi nums(n);
    rep(i, n) cin >> nums[i];

    vi sizes(n), reduced(n);
    rep(i, n) {
        ll x = nums[i];
        ll siz = 1;
        while (x % 2 == 0) {
            siz *= 2;
            x /= 2;
        }
        reduced[i] = x;
        sizes[i] = siz;
    }

    repp(i, 1, sz(sizes)) sizes[i] += sizes[i - 1];

    while (q--) {
        ll x;
        cin >> x;
        auto it = lower_bound(all(sizes), x);
        if (it == end(sizes)) {
            cout << "-1\n";
            continue;
        }
        cout << reduced[it - begin(sizes)] << '\n';
    }

    return 0;
}
