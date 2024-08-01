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


signed main()
{
    fast();

    int n, m;
    cin >> n >> m;

    vector<p2> edgelist;
    vector<vector<p2>> edges(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edgelist.emplace_back(a, b);
        edges[a].emplace_back(b, i);
        edges[b].emplace_back(a, i);
    }

    int ans = inf;
    rep(i, n)
    {
        vi tree(m);
        queue<int> q;
        vi depth(n, -inf);
        depth[i] = 0;
        q.emplace(i);
        while (sz(q))
        {
            int u = q.front();
            q.pop();

            repe(e, edges[u])
            {
                if (depth[e.first]==-inf)
                {
                    tree[e.second] = 1;
                    depth[e.first] = depth[u] + 1;
                    q.emplace(e.first);
                }
            }
        }

        rep(i, m)
        {
            if (tree[i]) continue;
            int a, b;
            tie(a, b) = edgelist[i];
            if (depth[a] == -inf || depth[b] == -inf) continue;
            ans = min(ans, depth[a] + depth[b] + 1);
        }
    }
    if (ans == inf) cout << -1;
    else cout << ans;

    return 0;
}
