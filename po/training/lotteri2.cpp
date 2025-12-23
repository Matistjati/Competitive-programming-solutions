#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define repe(i, arr) for (auto& i : arr)
#define rep(i, b) for(ll i = 0; i < (b); ++i)
#define repp(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)x.size())


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, t;
    cin >> n >> t;

    vi nums(n);
    repe(v, nums) cin >> v;

    int ways = 0;
    int tot = 0;

    rep(mask, 1 << n)
    {
        int sum = 0;
        rep(i, n) if (mask & (1 << i)) sum += nums[i];
        if (sum == t) ways++;
        tot++;
    }

    cout << fixed << setprecision(15) << (100*(ways + 0.) / tot) << '\n';

    return 0;
}
