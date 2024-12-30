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

signed main()
{
    fast();

    string x;
    cin >> x;
    vi good(255);
    good['a'] = 1;
    good['e'] = 1;
    good['i'] = 1;
    good['o'] = 1;
    good['u'] = 1;
    good['y'] = 1;
    repe(c, x)
    {
        if (good[tolower(c)]) cout << c;
    }

    return 0;
}
