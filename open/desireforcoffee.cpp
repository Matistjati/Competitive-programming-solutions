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

using p3 = tuple<ll,ll,ll>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    vector<p3> turtles(n);
    for (auto& [a,b,c] : turtles) {
        cin >> a >> b >> c;
    }
    sort(all(turtles), [](p3 a, p3 b) {
        return get<1>(a) + get<0>(a) < get<1>(b) + get<0>(b);
    });

    const int LIMIT = 1005;
    vector<int> dp(LIMIT),new_dp(LIMIT);
    for (auto [cap, weight, len] : turtles) {
        rep(c_w, LIMIT) {
            if (c_w > cap || c_w + weight > LIMIT) break;
            new_dp[c_w + weight] = max<int>(new_dp[c_w + weight], dp[c_w] + len);
        }

        dp = new_dp;
    }

    cout << *max_element(all(dp)) << '\n';

    return 0;
}
