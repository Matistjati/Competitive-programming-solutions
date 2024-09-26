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

bool possible(vi& nums, int m, int k)
{
    int f = m - k;
    if (f <= 0) return 1;

}

void solve()
{
    int n, k;
    cin >> n >> k;

    vi nums(n);
    rep(i, n) cin >> nums[i];
    sort(all(nums));

    if (sz(nums)==1)
    {
        cout << (nums.back() <= k-1 ? k : k - 1) << "\n";
        return;
    }

    int g = nums[0];
    repp(i, 1, n) g = gcd(g, nums[i]);
    if (g==1)
    {
        cout << n + k - 1 << "\n";
        return;
    }


    vi newnums;
    rep(i, n)
    {
        newnums.push_back(i * g);
    }
    nums = newnums;
    int lo = -1;
    int hi = n + k + 10;
    while (lo+1<hi)
    {
        int mid = (lo + hi) / 2;
        int cnt = 0;
        rep(i, n)
        {
            if (nums[i]<mid)
            {
                cnt++;
            }
        }
        if (cnt + k - 1 >= mid)
        {
            lo = mid;
        }
        else hi = mid;
    }
    cout << lo << "\n";

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
