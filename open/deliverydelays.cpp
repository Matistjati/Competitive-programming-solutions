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

    int n, m;
    cin >> n >> m;
    vector<vector<p2>> adj(n);
    rep(i, m)
    {
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        adj[a].emplace_back(b, w);
        adj[b].emplace_back(a, w);
    }
    int k;
    cin >> k;

    vector<tuple<int, int, int>> orders;
    rep(i, k)
    {
        int s, u, t;
        cin >> s >> u >> t;
        u--;
        orders.emplace_back(s, t, u);
    }

    vvi dist(n, vi(n, inf));
    rep(i, n)
    {
        priority_queue<p2> pq;
        pq.emplace(0, i);
        dist[i][i] = 0;
        while (sz(pq))
        {
            auto [d, u] = pq.top();
            pq.pop();
            d = -d;
            if (d > dist[i][u]) continue;
            repe(e, adj[u])
            {
                int d2 = d+e.second;
                if (d2<dist[i][e.first])
                {
                    dist[i][e.first] = d2;
                    pq.emplace(-d2, e.first);
                }
            }
        }
    }

    int lo = -1;
    int hi = 1e18;
    while (lo+1<hi)
    {
        int mid = (lo + hi) / 2;

        vi dp(k+1, inf);
        dp[0] = 0;
        // dp[i] = i have served [0,i]
        // i am located on on node 0
        // at earliest time, satisfying no wait > mid
        rep(i, k)
        {
            int st = dp[i];
            int hardestorder = -inf;
            int cumdist = 0;
            int last = 0;
            repp(j, i+1, k + 1)
            {
                auto [s, t, u] = orders[j-1];

                int leavetime = max(st,t);
                cumdist += dist[last][u];
                last = u;
                hardestorder = max(hardestorder, cumdist-s);
                if (hardestorder+leavetime>mid)
                {
                    break;
                }
                if (leavetime >= st) dp[j] = min(dp[j], leavetime + cumdist + dist[last][0]);
            }
        }
        if (dp.back() < inf)
        {
            hi = mid;
        }
        else lo = mid;
    }

    cout << hi;


    return 0;
}
