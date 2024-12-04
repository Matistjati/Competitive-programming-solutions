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

int hibit(int x)
{
    for (int i = 63; i >= 0; i--)
    {
        if (x & (1LL << i)) return i;
    }
}

void solve()
{
    int n;
    cin >> n;

    int seen = 0;
    vi ans;
    while (n)
    {
        int h = hibit(n);
        n ^= 1LL << h;
        if (seen | n) ans.push_back(seen | n);
        seen |= 1LL << h;
    }
    ans.push_back(seen);
    cout << sz(ans) << "\n";
    repe(u, ans) cout << u << " ";
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
