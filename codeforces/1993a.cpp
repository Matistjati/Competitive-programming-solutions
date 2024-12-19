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
    string s;
    cin >> s;
    map<char, int> cnt;
    repe(c, s) cnt[c]++;
    cnt.erase('?');

    int ans = 0;
    repe(c, cnt)
    {
        if (c.second>=n)
        {
            ans += n;
        }
        else
        {
            ans += c.second;
        }
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
