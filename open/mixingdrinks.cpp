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

const constexpr int mod = int(1e9 + 7);
signed main()
{
    fast();

    int n, p;
    cin >> n >> p;

    vector<p2> edges;
    vvi adj(n+1);
    rep(i, p)
    {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        edges.emplace_back(a, b);
        adj[b].push_back(a);
    }

    vi dp(n + 1);
    dp[0] = 1;
    int lo = 0;
    int s = 1;
    repp(i, 1, n + 1)
    {
        repe(e, adj[i])
        {
            while (lo<e)
            {
                s -= dp[lo];
                s %= mod;
                s += mod;
                s %= mod;
                lo++;
            }
        }

        dp[i] = s;
        s = (s + dp[i]) % mod;
    }
    cout << dp.back();
    return 0;
}
