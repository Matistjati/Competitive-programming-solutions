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

    int n, k;
    cin >> n >> k;

    vi nums(n);
    rep(i, n) cin >> nums[i];

    auto solve = [&](int mid) {
        vi dp(n + 1, -1e9);
        dp[0] = 0;
        repp(l, 1, n + 1) {
            int bal = 0;
            repp(j, l, n + 1) {
                bal += nums[j - 1] >= mid ? 1 : -1;
                if (bal > 0 && (j - l) % 2 == 0) dp[j] = max(dp[j], 1 + dp[l-1]);
            }
        }
        return dp.back();
    };

    int lo = -1;
    int hi = 1e9+1;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;

        int max_intervals = solve(mid);
        if (max_intervals >= k) lo = mid;
        else hi = mid;
    }
    cout << lo << '\n';


    return 0;
}
