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

    //ifstream in("e:/in.txt");
    //cin.rdbuf(in.rdbuf());

    int maxv = int(1e8) + 10;
    vi dp(maxv);

    int n, d;
    cin >> n >> d;
    vector<tuple<int, int, int>> turtles;
    rep(i, n)
    {
        int l, w, h;
        cin >> l >> w >> h;
        turtles.emplace_back(l, w, h);
    }
    sort(all(turtles), [](tuple<int, int, int> a, tuple<int, int, int> b)
        {
            return get<1>(a) > get<1>(b);
        });
    if (n==1)
    {
        cout << (get<0>(turtles[0]) > d);
        return 0;
    }
    int ans = 0;

    rep(i, n)
    {
        auto [l, w, h] = turtles[i];
        int bestsupport = dp[w];
        if (bestsupport + l > d)
        {
            ans++;
        }

        int u = w - 1;
        while (u+w>=sz(dp))
        {
            dp[u] = max(dp[u], h);
            u--;
        }

        repp(j, 1, u+1)
        {
            dp[j] = max(dp[j], h + dp[j + w]);
        }
    }
    cout << ans;

    return 0;
}
