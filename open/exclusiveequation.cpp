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


int main()
{
    cin.tie(0)->sync_with_stdio(0);

    using ull = unsigned long long;
    ull n, t;
    cin >> n >> t;

    vector<ull> nums(n);
    rep(i, n)
    {
        ull v, _;
        cin >> v >> _;
        nums[i] = v;
    }

    vector<ull> basis;
    auto reduce = [&](ull x)
    {
        repe(v, basis) x = min(x, x ^ v);
        return x;
    };

    auto insert = [&](ull x)
    {
        x = reduce(x);
        assert(x != 0);
        basis.push_back(x);
        sort(all(basis));
        reverse(all(basis));
    };

    rep(i, n)
    {
        if (reduce(nums[i])!=0)
        {
            insert(nums[i]);
        }
    }

    cout << (reduce(t) == 0 ? "possible" : "impossible") << '\n';

    return 0;
}
