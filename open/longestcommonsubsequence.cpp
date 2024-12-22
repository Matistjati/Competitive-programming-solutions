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

    int n, k;
    cin >> n >> k;

    set<string> seen;
    rep(i, n)
    {
        string x;
        cin >> x;
        seen.insert(x);
    }
    vector<string> data(all(seen));
    n = sz(seen);
    vector<vector<char>> pos(k, vector<char>(n));

    rep(i, n)
    {
        rep(j, k) pos[data[i][j] - 'A'][i] = j;
    }


    vi dp(k, 1);
    queue<p2> q;
    rep(i, k) q.emplace(i, 1);

    while (sz(q))
    {
        int c, d;
        tie(c, d) = q.front();
        q.pop();
        
        if (d < dp[c]) continue;

        rep(cc, k)
        {
            if (d + 1 <= dp[cc]) continue;
            bool good = 1;
            rep(i, n) good &= pos[c][i] < pos[cc][i];
            if (good)
            {
                dp[cc] = d + 1;
                q.emplace(cc, d + 1);
            }
        }
    }
    cout << *max_element(all(dp));

    return 0;
}
