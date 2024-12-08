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

    int n, m;
    cin >> n >> m;

    vi dp(1000, inf);
    dp[0] = 0;

    rep(i, 1000)
    {
        if (i % m == 0) dp[i] = min(dp[i], dp[i / m] + 1);
        for (int j = i - m + 1; j < i; j++)
        {
            if (j < 0) continue;
            dp[i] = min(dp[i], dp[j] + 1);
        }
    }

    int ans = 0;
    while (n >= 1000)
    {
        if (n % m != 0)
        {
            n -= (n % m);
            ans++;
        }

        if (n)
        {
            assert(n % m == 0);
            n /= m;
            ans++;
        }
    }
    cout << ans + dp[n] << endl;

	return 0;
}
