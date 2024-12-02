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
    int n;
    cin >> n;
    vi colors(n);
    rep(i, n) cin >> colors[i];
    map<int, int> colorcnt;
    rep(i, n) colorcnt[colors[i]]++;

    int ans = 0;
    int num_ones = 0;
    repe(c, colorcnt)
    {
        if (c.second == 1)
        {
            num_ones++;
        }
        else
        {
            ans++;
        }
    }
    ans += (num_ones + 1) / 2 * 2;

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
