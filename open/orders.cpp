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

    int n;
    cin >> n;
    vi items(n);
    rep(i, n) cin >> items[i];

    vvi dp(n + 1, vi(30001));
    vector<vector<p2>> from(n + 1, vector<p2>(30001, p2(-1,-1)));
    dp[0][0] = 1;

    rep(i, n)
    {
        rep(j, sz(dp[0]))
        {
            if (dp[i][j] > 0) from[i + 1][j] = p2(i, j);
            dp[i + 1][j] += dp[i][j];
        }
        rep(j, sz(dp[0]))
        {
            if (j + items[i] >= sz(dp[0])) continue;
            if (dp[i+1][j]>0)
            {
                int w = j + items[i];
                dp[i + 1][w]+=dp[i+1][j];
                dp[i + 1][w] = min(2LL, dp[i + 1][w]);
                from[i + 1][w] = p2(i+1, j);
            }
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;
        if (dp.back()[t]==0)
        {
            cout << "Impossible\n";
        }
        else if (dp.back()[t] == 1)
        {
            p2 state = p2(n, t);
            vi res;
            while (from[state.first][state.second].first!=-1)
            {
                p2 p = from[state.first][state.second];
                if (p.first==state.first)
                {
                    res.push_back(state.first);
                }
                state = p;
            }
            sort(all(res));
            repe(u, res) cout << u << " ";
            cout << '\n';
        }
        else
        {
            cout << "Ambiguous\n";
        }
    }

    return 0;
}
