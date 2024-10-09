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


int dp[151][151][51];
signed main()
{
    fast();



    int t;
    cin >> t;
    while (t--)
    {
        int cg, n1, n5, n10;
        cin >> cg >> n1 >> n5 >> n10;

        rep(i, cg + 1) rep(j, n5 + 51) rep(k, n10 + 1) dp[i][j][k] = inf;
        int tot = n1 + n5 * 5 + n10 * 10;
        dp[0][n5][n10] = 0;

        rep(coke, cg)
        {
            rep(c5, n5 + 51)
            {
                rep(c10, n10 + 1)
                {
                    int c = dp[coke][c5][c10];
                    if (c == inf) continue;
                    int num_one = (tot - c5 * 5 - c10 * 10 + coke * 8);
                    // buy with a 10-coin
                    if (c10>=1) dp[coke + 1][c5][c10 - 1] = min(dp[coke + 1][c5][c10 - 1], c+1);
                    // buy with a 10-coin and 3 ones
                    if (c10>=1&&num_one>=3) dp[coke + 1][c5+1][c10 - 1] = min(dp[coke + 1][c5 + 1][c10 - 1], c+4);
                    // buy with two 5-coins
                    if (c5>=2) dp[coke + 1][c5-2][c10] = min(dp[coke + 1][c5-2][c10], c+2);
                    // buy with one 5-coin and 3 ones
                    if (c5 >= 1 && num_one >= 3) dp[coke + 1][c5 - 1][c10] = min(dp[coke + 1][c5 - 1][c10], c + 4);
                    // buy with 8 1-coins
                    if (num_one >= 8) dp[coke + 1][c5][c10] = min(dp[coke + 1][c5][c10], c + 8);
                }
            }
        }
        int ans = inf;
        rep(i, n5 + 1) rep(j, n10 + 1) ans = min(ans, dp[cg][i][j]);
        cout << ans << "\n";
    }

    return 0;
}
