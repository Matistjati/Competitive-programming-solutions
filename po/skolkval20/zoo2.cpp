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

int n, k;
int dp[20][20];
vvi goodafter;
int count(int i, int prev)
{
    if (i == n) return 1;
    int& v = dp[i][prev + 1];
    if (v != -1) return v;

    int ret = 0;
    rep(a, k)
    {
        if (prev == -1 || goodafter[prev][a]) ret += count(i + 1, a);
    }


    return v = ret;
}

signed main()
{
    fast();


    memset(dp, -1, sizeof(dp));
    int m;
    cin >> n >> k >> m;
    goodafter.resize(k, vi(k, 1));
    rep(i, k) goodafter[i][i] = 0;
    rep(_, m)
    {
        string enemies;
        cin >> enemies;
        rep(i, sz(enemies))
        {
            repp(j, i + 1, sz(enemies))
            {
                int a = enemies[i] - 'A';
                int b = enemies[j] - 'A';
                goodafter[a][b] = 0;
                goodafter[b][a] = 0;
            }
        }
    }
    cout << count(0, -1);

    return 0;
}
