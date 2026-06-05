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

consteval int pow3(int x) {
    int ret = 1;
    rep(i, x) ret *= 3;
    return ret;
}
constexpr int pow3s[10] = { pow3(0),
                 pow3(1),
                 pow3(2),
                 pow3(3),
                 pow3(4),
                 pow3(5),
                 pow3(6),
                 pow3(7),
                 pow3(8),
                 pow3(9)
};


vi nums;
vector<array<int, 10>> dists;
ll dp[pow3(10)][100];
ll tot(int i, array<int, 10>& occs) {
    int mask = 0;
    rep(i, 10) mask += occs[i] * pow3s[i];
    if (dp[mask][i] != -1) return dp[mask][i];
    if (i == sz(nums)) return 0;

    ll ret = -inf;
    {
        bool good = 1;
        rep(j, 10) {
            occs[j]+=dists[i][j];
            good &= occs[j] < 3;
        }

        if (good) ret = max(ret, nums[i] + tot(i + 1, occs));

        rep(j, 10) {
            occs[j] -= dists[i][j];
        }
    }
    ret = max(ret, tot(i + 1, occs));

    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(dp, -1, sizeof(dp));

    int n;
    cin >> n;
    nums.resize(n);
    dists.resize(n);
    rep(i, n) {
        cin >> nums[i];
        array<int, 10> vals{};
        for (char c : to_string(nums[i])) {
            vals[c - '0']++;
        }
        dists[i] = vals;
    }

    array<int, 10> occs{};
    cout << tot(0, occs) << '\n';


    return 0;
}
