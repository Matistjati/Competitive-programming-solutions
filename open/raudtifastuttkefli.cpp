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


signed main()
{
    fast();

    int n, k;
    cin >> n >> k;
    vi len(n), dopamine(n);
    rep(i, n) cin >> len[i] >> dopamine[i];
    int t;
    cin >> t;
    if (t>int(1e5)+10)
    {
        cout << accumulate(all(dopamine), 0LL) << "\n";
        return 0;
    }

    int ans = 0;

    vi nextdp(t + 1, -inf);
    vi dp(t + 1);
    rep(i, n)
    {
        rep(j, t + 1)
        {
            if (j-k>=0) nextdp[j] = max(nextdp[j], dp[j - k]);
            if (j - len[i] >= 0) nextdp[j] = max(nextdp[j], dopamine[i] + dp[j - len[i]]);
        }

        dp = nextdp;
        ans = max(ans, *max_element(all(dp)));
        nextdp.assign(t + 1, -inf);
    }

    cout << ans << "\n";

    return 0;
}
