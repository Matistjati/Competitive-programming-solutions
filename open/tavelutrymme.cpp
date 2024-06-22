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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    int n, r, c;
    cin >> n >> r >> c;

    vector<vector<p2>> dp(r, vector<p2>(c+1,p2(inf, inf)));
    dp[0][0] = p2(0, 0);
    rep(it, n)
    {
        int v;
        cin >> v;
        vector<vector<p2>> newdp(r, vector<p2>(c+1, p2(inf, inf)));
        rep(i, r)
        {
            rep(j, c+1)
            {
                if (dp[i][j].first == inf) continue;
                if (j+v<=c) // place board 1 curr row
                {
                    newdp[i][j + v] = min(newdp[i][j + v], dp[i][j]);
                }
                if (i+1<r) // place board 1 next row
                {
                    newdp[i+1][v] = min(newdp[i+1][v], dp[i][j]);
                }
                if (dp[i][j].second+v<=c) // place board 2 curr row
                {
                    newdp[i][j] = min(newdp[i][j], p2(dp[i][j].first, dp[i][j].second + v));
                }
                if (dp[i][j].first+1<r) // place board 2 next row
                {
                    newdp[i][j] = min(newdp[i][j], p2(dp[i][j].first+1, v));
                }
            }
        }

        int good = 0;
        rep(i, r) rep(j, c+1) good |= newdp[i][j].first != inf;
        if (!good)
        {
            cout << it;
            return 0;
        }
        dp = newdp;
    }
    cout << n;

    return 0;
}
