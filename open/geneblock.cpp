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

    vi dp(100, inf);
    dp[0] = 0;
    for (int i = 7; i < 100; i += 10)
    {
        rep(j, sz(dp))
        {
            if (j - i < 0) continue;
            dp[j] = min(dp[j], 1 + dp[j - i]);
        }
    }

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        if (n<100)
        {
            cout << (dp[n] != inf ? dp[n] : -1) << "\n";
        }
        else
        {
            if (n % 10 == 7) cout << 1;
            else if (n % 10 == 4) cout << 2;
            else if (n % 10 == 1) cout << 3;
            else if (n % 10 == 8) cout << 4;
            else if (n % 10 == 5) cout << 5;
            else if (n % 10 == 2) cout << 6;
            else if (n % 10 == 9) cout << 7;
            else if (n % 10 == 6) cout << 8;
            else if (n % 10 == 3) cout << 9;
            else if (n % 10 == 0) cout << 10;
            else cout << -1;
            cout << "\n";
        }
    }



    return 0;
}
