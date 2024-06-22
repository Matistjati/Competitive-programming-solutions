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

int marked[2500];
int furthest_node;
int furthest_dist;

void dfs(int u, int p, int d, vvi& edges)
{
    if (d>furthest_dist)
    {
        furthest_dist = d;
        furthest_node = u;
    }
    marked[u] = 1;
    repe(e, edges[u]) if (e != p) dfs(e, u, d + 1, edges);
}

bool getpath(int a, int b, int p, vi& path, vvi& adj)
{
    if (a==b)
    {
        path.push_back(a);
        return 1;
    }

    repe(e, adj[a]) if (e != p)
    {
        if (getpath(e,b,a,path,adj))
        {
            path.push_back(a);
            return 1;
        }
    }

    return 0;
}

signed main()
{
    fast();

    int n;
    cin >> n;
    vector<p2> edges;
    rep(i, n-1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges.emplace_back(a, b);
    }
    int ans = inf;
    p2 rem;
    p2 add;
    rep(i, sz(edges))
    {
        rep(j, 2500) marked[j] = 0;
        vvi adj(n);
        rep(j, n-1)
        {
            if (i == j) continue;
            adj[edges[j].second].emplace_back(edges[j].first);
            adj[edges[j].first].emplace_back(edges[j].second);
        }

        furthest_dist = -1;
        dfs(0, 0, 0, adj);
        int f11 = furthest_node;
        furthest_dist = -1;
        dfs(furthest_node, furthest_node, 0, adj);
        int f12 = furthest_node;

        int d1 = furthest_dist;
        int notmarked;
        rep(j, n)if (!marked[j]) notmarked = j;
        furthest_dist = -1;
        dfs(notmarked, notmarked, 0, adj);
        int f21 = furthest_node;
        furthest_dist = -1;
        dfs(furthest_node, furthest_node, 0, adj);
        int f22 = furthest_node;
        int d2 = furthest_dist;
        int cost = max(d1, d2);
        cost = max(cost, (d1+1) / 2 + (d2+1) / 2 + 1);
        if (cost<ans)
        {
            ans = cost;
            rem = edges[i];
            vi p1;
            getpath(f11, f12, f11, p1, adj);
            vi p2;
            getpath(f21, f22, f21, p2, adj);
            add = make_pair(p1[sz(p1) / 2], p2[sz(p2) / 2]);
        }
    }
    cout << ans << "\n";
    cout << rem.first + 1 << " " << rem.second + 1 << "\n";
    cout << add.first + 1 << " " << add.second + 1 << "\n";

    return 0;
}
