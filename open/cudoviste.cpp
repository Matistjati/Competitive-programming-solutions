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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    rep(i, r) cin >> grid[i];

    vector<p2> delta = { {0,0},{0,1},{1,0},{1,1} };
    vi ans(5);
    rep(i, r - 1)
    {
        rep(j, c - 1)
        {
            int bcnt = 0;
            int ccnt = 0;
            repe(d, delta)
            {
                p2 np = p2(i + d.first, j + d.second);
                bcnt += grid[np.first][np.second] == '#';
                ccnt += grid[np.first][np.second] == 'X';
            }
            if (bcnt) continue;
            ans[ccnt]++;
        }
    }
    repe(u, ans) cout << u << "\n";

    return 0;
}
