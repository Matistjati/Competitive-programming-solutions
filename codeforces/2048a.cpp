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

int tryall(string& x, string built, int i)
{
    if (i==sz(x))
    {
        if (built.empty()) return 0;
        return stoi(built) % 33 == 0;
    }

    int ret = 0;

    ret |= tryall(x, built + x[i], i + 1);
    if (i+1<sz(x) && x[i]=='3' && x[i+1]=='3')
    {
        ret |= tryall(x, built, i + 2);
    }

    return ret;
}

void solve()
{
    int n;
    cin >> n;
    if (n%33==0)
    {
        cout << "YES\n";
        return;
    }
    string s = to_string(n);
    cout << (tryall(s, "", 0) ? "YES" : "NO") << "\n";
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
