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
    int n, k, q;
    cin >> n >> k >> q;

    vi nums(n);
    rep(i, n) cin >> nums[i];
    rep(i, n) nums[i] -= i;
    vi ans(n);

    set<p2> most_common;
    map<int, int> count;
    auto insert = [&](int v)
    {
        if (most_common.count(p2(count[v],v))) most_common.erase(p2(count[v], v));
        count[v]++;
        most_common.insert(p2(count[v], v));
    };
    auto erase = [&](int v)
    {
        if (most_common.count(p2(count[v], v))) most_common.erase(p2(count[v], v));
        count[v]--;
        if (count[v]) most_common.insert(p2(count[v], v));
    };
    rep(i, k)
    {
        insert(nums[i]);
    }

    rep(i, n)
    {
        ans[i] = k - prev(end(most_common))->first;
        erase(nums[i]);
        if (i + k >= n) break;
        insert(nums[i + k]);
    }

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        l--; r--;
        cout << ans[l] << "\n";
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
