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

    int n;
    cin >> n;
    vector<string> grid(n);
    rep(i, n) cin >> grid[i];

    const int mod = (1LL << 31) - 1;

    vvi dp(n, vi(n));
    vvi dp2(n, vi(n));
    dp[0][0] = 1;
    dp2[0][0] = 1;
    rep(i, n)
    {
        rep(j, n)
        {
            if (grid[i][j] == '#') continue;
            if (i) dp[i][j] += dp[i - 1][j];
            if (i) dp2[i][j] |= dp2[i - 1][j];
            if (j) dp[i][j] += dp[i][j - 1];
            if (j) dp2[i][j] |= dp2[i][j - 1];
            dp[i][j] %= mod;
        }
    }

    if (dp2.back().back())
    {
        cout << dp.back().back();
    }
    else
    {
        vvi vis(n, vi(n));
        queue<p2> q;
        q.emplace(0, 0);
        vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
        while (sz(q))
        {
            int r, c;
            tie(r, c) = q.front();
            q.pop();
            if (vis[r][c]) continue;
            vis[r][c] = 1;
            repe(dir, dirs)
            {
                p2 np = p2(r + dir.first, c + dir.second);
                if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= n || grid[np.first][np.second] == '#') continue;
                q.emplace(np);
            }
        }
        if (vis.back().back())
        {
            cout << "THE GAME IS A LIE";
        }
        else cout << "INCONCEIVABLE";
    }

    return 0;
}
