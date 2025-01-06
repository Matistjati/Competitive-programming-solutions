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

string s, a, b;

int dp[5001][5001];

int best(int i, int j)
{
    int& v = dp[i][j];
    if (v != -1) return v;
    int ret = 0;

    int t = i + j;
    if (i<sz(a) && a[i]==s[t])
    {
        ret = max(ret, 1 + best(i + 1, j));
    }
    if (j<sz(b) && b[j]==s[t])
    {
        ret = max(ret, 1 + best(i, j + 1));
    }

    return v = ret;
}

signed main()
{
    fast();

    memset(dp, -1, sizeof(dp));
    cin >> s >> a >> b;
    cout << (best(0, 0) == sz(s) ? "yes" : "no");

    return 0;
}
