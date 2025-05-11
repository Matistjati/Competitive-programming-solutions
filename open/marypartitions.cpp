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

int brute(int s, int b, int m, int n)
{
    if (s > n) return 0;
    if (s == n) return 1;
    if (b > n) return 0;

    int ret = 0;
    ret += brute(s + b, b, m, n);
    ret += brute(s, b * m, m, n);

    return ret;
}

signed main()
{
    fast();

    int dp[101][15][10001];
    repp(b, 3, 101)
    {
        memset(dp[b], 0, sizeof(dp[b]));
        dp[b][0][0] = 1;
        int m = 1;
        rep(i, 100)
        {
            
            rep(j, 10001)
            {
                if (j + m < 10001) dp[b][i][j + m] += dp[b][i][j];
                if (i + 1 < 15) dp[b][i+1][j] += dp[b][i][j];
            }
            if (m <= 10001) m *= b;
        }
    }


    int t;
    cin >> t;
    while (t--)
    {
        int k, m, n;
        cin >> k >> m >> n;

        cout << k << " " << dp[m][14][n] << "\n";
    }


    return 0;
}
