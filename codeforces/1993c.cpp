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
    int n, k;
    cin >> n >> k;

    vi nums(n);
    rep(i, n) cin >> nums[i];

    int s = *max_element(all(nums));

    vvi cong(n);
    vi status(n);
    int numon = 0;
    rep(i, n)
    {
        cong[nums[i] % k].push_back(i);
        int delta = s - nums[i];
        int numflicks = delta / k;
        if (numflicks%2==0)
        {
            numon++;
            status[i] = 1;
        }
    }

    repp(t, s + 1, s + k)
    {
        if (numon==n)
        {
            cout << t-1 << "\n";
            return;
        }
        repe(u, cong[t % k])
        {
            int delta = s - nums[u];
            int numflicks = delta / k;
            if (status[u] == 1) numon--;
            else numon++;
            status[u] ^= 1;
        }
    }
    if (numon == n)
    {
        cout << s+k-1 << "\n";
        return;
    }
    cout << "-1\n";
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
