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

    int n, _;
    cin >> n >> _;

    vi nums(n - 1);
    rep(i, n - 1)
    {
        cout << "? " << i + 1 << " " << i + 2 << endl;
        cin >> nums[i];
    }

    repp(i, 1, n - 1) nums[i] ^= nums[i - 1];
    vi occs(2 * n + 1);
    rep(i, n - 1) occs[nums[i]]++;

    vector<p2> degs;
    rep(i, sz(occs)) if (occs[i]) degs.emplace_back(i, occs[i]);

    repp(startdeg, 1, n + 1)
    {
        int tot = startdeg;
        bool good = 1;
        for (auto [xored, cnt] : degs)
        {
            int deg = xored ^ startdeg;
            tot += deg * cnt;
            good &= deg > 0;
        }
        if (!good || tot != 2 * n - 2) continue;
        cout << "! " << startdeg;
        rep(i, n - 1)
        {
            int deg = nums[i] ^ startdeg;
            cout << " " << deg;
        }
        return 0;
    }


    return 0;
}
