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
#define clz(x) _lzcnt_u32(x)
#else
#define clz(x) __builtin_clz(x)
#endif


void solve()
{
    int n;
    cin >> n;

    vi nums(n);
    rep(i, n) cin >> nums[i];
    sort(all(nums));

    int ans = inf;
    int numodd = 0;
    rep(i, n) numodd += nums[i] % 2;

    if (numodd==0||numodd==n)
    {
        cout << "0\n";
        return;
    }
    
    if (nums.back() % 2 == 1)
    {
        ans = n - numodd;
    }
    else
    {
        int largestodd = -1;
        rep(i, n)
        {
            if (nums[i]%2)
            {
                largestodd = max(largestodd, nums[i]);
            }
        }
        vi iseven;
        repe(u, nums) if (u % 2 == 0) iseven.push_back(u);
        bool good = 1;
        int s = largestodd;
        repe(u, iseven)
        {
            good &= u <= s;
            s += u;
        }

        if (good) ans = n - numodd;
        else ans = n - numodd + 1;
    }
    
    

    cout << ans << "\n";
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
