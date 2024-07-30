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

const int mod = int(1e9 + 7);
signed main()
{
    fast();

    string s;
    cin >> s;
    vi leftest(26, inf);
    int n = sz(s);
    vvi transitions(n+1);

    for (int i = n; i >= 0; i--)
    {
        transitions[i] = leftest;
        if (i) leftest[s[i-1]-'a'] = i;
    }

    vi dp(n+1);
    dp[0] = 1;
    rep(i, n)
    {
        repe(t, transitions[i])
        {
            if (t == inf) continue;
            dp[t] = (dp[t] + dp[i]) % mod;
        }
    }
    dp[0] = 0;
    int ans = 0;
    rep(i, n+1) ans = (ans + dp[i]) % mod;
    cout << ans;

    return 0;
}
