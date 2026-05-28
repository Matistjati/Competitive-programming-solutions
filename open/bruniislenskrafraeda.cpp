#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
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

    int n, T;
    cin >> n >> T;
    int ans = T;

    vector<p2> good;
    vector<p2> bad;
    rep(i, n) {
        int t, f;
        cin >> t >> f;
        if (f >= t) {
            good.emplace_back(t, f);
        }
        else {
            bad.emplace_back(f, t);
        }
    }
    sort(all(good));
    sort(all(bad));
    reverse(all(bad));
    for (auto [t, f] : good) {
        if (T >= t) {
            T -= t;
            T += f;
            ans += f;
        }
    }

    //cerr << "T is: " << T << '\n';

    vector<int> dp(1e6 + 10, INT_MIN);
    // dp[curr fire]=max tot
    dp[T] = ans;

    for (auto [f, t] : bad) {
        rep(i, sz(dp)) {
            if (i - f + t >= sz(dp)) continue;
            if (t > i - f + t) continue;
            dp[i] = max(dp[i], dp[i - f + t] + (int)f);
        }
    }

    cout << *max_element(all(dp)) << '\n';


    return 0;
}
