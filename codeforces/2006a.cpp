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
    int n;
    cin >> n;

    vi deg(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        deg[a]++;
        deg[b]++;
    }

    int zero = 0;
    int one = 0;
    int q = 0;
    int unimportant = 0;
    string s;
    cin >> s;
    repp(i, 1, n)
    {
        if (deg[i] == 1)
        {
            if (s[i] == '0') zero++;
            if (s[i] == '1') one++;
            if (s[i] == '?') q++;
        }
        else if (s[i] == '?') unimportant++;
    }

    int ans = 0;

    if (s[0]!='?')
    {
        if (s[0] == '1') ans += zero;
        if (s[0] == '0') ans += one;
        ans += (q + 1) / 2;
    }
    else
    {
        if (zero!=one)
        {
            ans = max(zero, one);
            ans += q / 2;
        }
        else
        {
            ans += zero;
            if (unimportant % 2 == 1) ans += (q + 1) / 2;
            else ans += q / 2;
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
