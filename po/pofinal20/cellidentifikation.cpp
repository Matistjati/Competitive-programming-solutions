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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    int n, k;
    cin >> n >> k;

    vi exists(1LL << k);
    rep(i, n)
    {
        string s;
        cin >> s;
        exists[stoi(s, 0, 2)] = i+1;
    }

    vi dp(1LL << k);
    for (int mask = sz(dp) - 1; mask >= 0; mask--)
    {
        if (exists[mask])
        {
            if (dp[mask] == 0) dp[mask] = exists[mask];
            else dp[mask] = -2;
        }
        if (dp[mask] == 0) continue;
        rep(i, k)
        {
            if (mask&(1LL<<i))
            {
                int new_mask = mask ^ (1LL << i);
                if (dp[mask] == -2) dp[new_mask] = -2;
                else
                {
                    if (dp[new_mask] == 0 || dp[new_mask] == dp[mask]) dp[new_mask] = dp[mask];
                    else dp[new_mask] = -2;
                }
            }
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        string s;
        cin >> s;
        int mask = stoi(s, 0, 2);
        if (dp[mask] == 0) cout << "finns ej";
        else if (dp[mask] == -2) cout << "vet ej";
        else cout << dp[mask];
        cout << "\n";
    }

    return 0;
}

