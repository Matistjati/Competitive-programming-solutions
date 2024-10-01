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

signed main()
{
    fast();

    //ifstream in("c:\\users\\matis\\source\\repos\\comp_prog\\x64\\debug\\in.txt");
    //cin.rdbuf(in.rdbuf());

    int n;
    cin >> n;

    const int maxy = int(1e5) + 10;

    vi num_single(maxy);
    vi num_pair(maxy);
    rep(i, n)
    {
        int x, y, w;
        cin >> x >> y >> w;
        if (w == 1) num_single[y]++;
        if (w == 2) num_pair[y]++;
    }

    int ans = 0;
    int prev = 0;
    rep(i, maxy)
    {
        ans += min(prev, num_pair[i]);
        prev -= min(prev, num_pair[i]);
        int g = min(prev, num_single[i]);
        ans += g;
        num_single[i] -= g;
        prev = num_pair[i] + num_single[i];
    }
    
    cout << ans;

    return 0;
}
