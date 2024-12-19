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

int k;
int nc, numrems;
int dp[2][int(5e5)];
int best(vi& arr, int i, bool taken) // maximize num zero
{
    int ret = -inf;
    if (taken)
    {
        if (k==nc && i%k==0)
        {
            ret =0;
            return ret;
        }
        if (k!=nc && i%k==nc)
        {
            ret = 0;
            return ret;
        }
    }
    if (i == sz(arr)) return ret;
    int& v = dp[taken][i];
    if (v != -1) return v;
    
    //if (i % (k + 1) == nc) ret = 0;
    ret = max(ret, (arr[i] == 1) + best(arr, i + 1, 1));
    if (i+k <= sz(arr))
    {
        ret = max(ret, best(arr, i + k, taken));
    }
    return v=ret;
}


void solve()
{
    int n;
    cin >> n >> k;

    vi nums(n);
    rep(i,n) cin >> nums[i];

    if (k>=n)
    {
        sort(all(nums));
        cout << nums[(n+1)/2-1] << "\n";
        return;
    }

    numrems = 0;
    nc = n;
    while (nc>k)
    {
        nc -= k;
        numrems++;
    }

    int lo = -1;
    int hi = int(1e9 + 10);
    while (lo+1<hi)
    {
        int mid = (lo + hi) / 2;

        rep(i, n) dp[0][i] = dp[1][i] = - 1;
        vi isgood(n);
        rep(i, n) isgood[i] = nums[i] >= mid;

        if (best(isgood, 0, 0) * 2 >= nc + 1)
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
