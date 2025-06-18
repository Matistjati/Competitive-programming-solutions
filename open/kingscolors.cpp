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

const int mod = int(1e9 + 7);

int n, k;
int dp[2501][2502];
int cnt(int i, int used)
{
    if (i==n)
    {
        return used == k;
    }
    if (used > k) return 0;
    if (dp[i][used] != -1) return dp[i][used];
    int ret = 0;
    if (used) ret += cnt(i + 1, used) * (used - 1) % mod;
    ret += cnt(i + 1, used + 1) * (k - used) % mod;

    return dp[i][used] = ret % mod;
}

signed main()
{
    fast();

    memset(dp, -1, sizeof(dp));
    cin >> n >> k;

    int ans = 0;
    cout << cnt(0, 0);

    return 0;
}
