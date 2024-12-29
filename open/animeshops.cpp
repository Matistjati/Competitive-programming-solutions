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

    int n, m, k;
    cin >> n >> m >> k;
    vi hasanime(n);
    rep(i, k)
    {
        int u;
        cin >> u;
        hasanime[u - 1] = 1;
    }

    vvi adj(n);
    vector<p2> edges;
    rep(i, m)
    {
        int u, v;
        cin >> u >> v;
        u--; v--;
        edges.emplace_back(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vi who(n,-1);
    vi dist(n, inf);
    queue<tuple<int,int,int>> q;
    rep(i, n) if (hasanime[i]) q.emplace(0, i, i), dist[i] = 0, who[i]=i;
    while (sz(q))
    {
        int d, u, p;
        tie(d, u, p) = q.front();
        q.pop();

        if (d > dist[u]) continue;
        
        repe(e, adj[u])
        {
            if (d+1<dist[e])
            {
                who[e] = p;
                dist[e] = d + 1;
                q.emplace(d + 1, e, p);
            }
        }
    }
    vi ans(n, inf);
    repe(e, edges)
    {
        int u, v;
        tie(u, v) = e;
        if (who[u]!=who[v])
        {
            ans[who[u]] = min(ans[who[u]], 1+dist[u] + dist[v]);
            ans[who[v]] = min(ans[who[v]], 1+dist[u] + dist[v]);
        }
    }
    rep(i, n) if (!hasanime[i]) ans[i] = dist[i];

    rep(i, n)
    {
        if (ans[i] == inf) cout << "-1 ";
        else cout << ans[i] << " ";
    }

    return 0;
}
