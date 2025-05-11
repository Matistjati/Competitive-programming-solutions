#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

signed main()
{
    fast();


    int k;
    cin >> k;
    vi tests(k);
    repe(t, tests) cin >> t;
    sort(all(tests));

    vvi dp(1 << k, vi(9, inf));
    dp[0][1] = 1;

    rep(mask, 1 << k)
    {
        repp(j, 1, 9)
        {
            rep(d, k)
            {
                if ((mask | (1 << d)) == mask) continue;
                if (dp[mask][j] == inf) continue;
                int r = dp[mask][j];
                int len = tests[d];

                //cout << "dp[" << (bitset<3>(mask).to_string()) << "][" << j << "] = " << r << "\n";

                int margin;
                if (len > j)
                {
                    margin = len - (j-1);
                    r += margin;
                }
                else
                {
                    r += 1;
                    margin = 1;
                }

                dp[mask | (1 << d)][margin] = min(dp[mask | (1 << d)][margin], r);
            }
        }
    }

    int ans = inf;
    rep(j, 9) ans = min(ans, dp[(1 << k) - 1][j]);
    cout << ans - 1;


    return 0;
}
