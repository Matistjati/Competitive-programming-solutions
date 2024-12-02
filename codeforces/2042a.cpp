#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

void solve()
{
    int n, k;
    cin >> n >> k;
    vi nums(n);
    rep(i, n) cin >> nums[i];

    int ans = 0;
    int s = accumulate(all(nums), 0LL);
    if (s <= k)
    {
        cout << k - s << "\n";
        return;
    }

    sort(all(nums));
    reverse(all(nums));
    int i = 0;
    int take = 0;
    int last = -1;
    while (take < k)
    {
        last = nums[i];
        take += nums[i];
        i++;
    }
    if (take==k)
    {
        cout << "0\n";
        return;
    }
    cout << k - (take - last) << "\n";
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
