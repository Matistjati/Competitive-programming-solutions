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
    int n, m;
    cin >> n >> m;
    vi nums(m);
    rep(i, m) cin >> nums[i];
    reverse(all(nums));

    vi ans(n);
    vector<set<int>> forbidden(n);
    rep(i, n)
    {
        bool good = 0;
        rep(j, m)
        {
            if (forbidden[i].find(nums[j])==forbidden[i].end())
            {
                ans[i] = nums[j];
                good = 1;
                break;
            }
        }
        if (!good)
        {
            cout << "-1\n";
            return;
        }
        for (int j = 2 * i + 1; j < n; j+=i+1)
        {
            forbidden[j].insert(ans[i]);
        }
        
    }

    rep(i, n)
    {
        cout << ans[i] << " ";
    }
    cout << "\n";
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
