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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int maxn = int(2e5+10);
int dp[2][maxn];
int c;
int best(int u, int p, bool p_strength, vi& gold, vvi& edges)
{
    int& v = dp[p_strength][u];
    if (v != -1) return v;

    int ret = 0;

    // strengthen me
    {
        int value = gold[u];
        if (p_strength) value -= c*2;

        repe(e, edges[u])
        {
            if (e == p) continue;
            value += best(e, u, 1, gold, edges);
        }
        ret = max(ret, value);
    }
    // don't
    {
        int value = 0;

        repe(e, edges[u]) if (e != p) value += best(e, u, 0, gold, edges);
        ret = max(ret, value);
    }

    return v = ret;
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n >> c;

        vi money(n);
        rep(i, n) cin >> money[i];

        vvi edges(n);
        rep(i, n-1)
        {
            int a, b;
            cin >> a >> b;
            a--; b--;
            edges[a].push_back(b);
            edges[b].push_back(a);
        }

        rep(i, 2) rep(j, n) dp[i][j] = -1;
        cout << best(0, 0, 0, money, edges) << "\n";
    }

    return 0;
}
