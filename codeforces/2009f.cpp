#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

void solve()
{
    int n, q;
    cin >> n >> q;

    vi nums(n);
    rep(i, n) cin >> nums[i];
    int t = 0;
    rep(i, n) t += nums[i];
    
    vi pref(nums);
    rep(i, n) pref.push_back(nums[i]);
    repp(i, 1, sz(pref)) pref[i] += pref[i - 1];
    auto rsq = [&](int l, int r)
    {
        if (l) l = pref[l - 1];
        return pref[r] - l;
    };

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--; r--;
        int rblock = r / n;
        int lblock = l / n;
        int ans = (rblock - lblock - 1) * t;
        r -= rblock * n;
        l -= lblock * n;
        ans += rsq(rblock, rblock + r);
        ans += rsq(lblock+l, lblock+n-1);
        cout << ans << "\n";
    }

}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
