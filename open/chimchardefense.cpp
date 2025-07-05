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


signed main()
{
    fast();

    int n;
    cin >> n;

    vi hp(n), dmg(n), cost(n);
    repe(v, hp) cin >> v;
    repe(v, dmg) cin >> v;
    repe(v, cost) cin >> v;

    const int maxdmg = 5000 * 2 + 2;
    vvi dp(n + 1, vi(maxdmg, -inf));
    dp.back()[0] = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        rep(j, maxdmg)
        {
            // 1: don't activate
            dp[i][j] = max(dp[i][j], min(hp[i], j) + dp[i + 1][j]);

            // do activate
            if (j - dmg[i] >= 0) dp[i][j] = max(dp[i][j], min(hp[i], j) + dp[i + 1][j - dmg[i]] - cost[i]);
        }
    }

    int ans = 0;
    rep(i, maxdmg) ans = max(ans, dp[0][i]);
    cout << ans;

    return 0;
}
