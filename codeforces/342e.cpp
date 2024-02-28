#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
const int inf = int(1e9);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#define _LOCAL _DEBUG
#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Centroid
{
    vi par, size, vis;
    vvi adj;
    Centroid(vvi adj) : adj(adj), par(sz(adj)), size(sz(adj)), vis(sz(adj))
    {
        build(0, -1);
    }

    int get_size(int u, int p)
    {
        if (vis[u]) return 0;
        size[u] = 1;
        repe(e, adj[u])
        {
            if (e != p) size[u] += get_size(e, u);
        }
        return size[u];
    }

    int find_centroid(int u, int p, int n)
    {
        repe(e, adj[u])
        {
            if (e == p) continue;
            if (!vis[e] && size[e] > n / 2) return find_centroid(e, u, n);
        }
        return u;
    }

    void build(int u, int p)
    {
        get_size(u, u);

        int c = find_centroid(u, p, size[u]);
        vis[c] = 1;
        par[c] = p;

        repe(e, adj[c])
        {
            if (e != p && !vis[e]) build(e, c);
        }
    }
};

const int maxn = int(2e5 + 10);
int depth[maxn];
int tin[maxn];
int tout[maxn];
int up[maxn][19];
int timer = 0;
void dfs(int u, int p, vvi& adj)
{
    tin[u] = timer++;
    depth[u] = depth[p] + 1;
    up[u][0] = p;

    repp(d, 1, 19)
    {
        up[u][d] = up[up[u][d - 1]][d - 1];
    }

    repe(e, adj[u]) if (e != p) dfs(e, u, adj);

    tout[u] = timer++;
}

bool isancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b)
{
    if (isancestor(a, b)) return a;
    if (isancestor(b, a)) return b;
    for (int d = 18; d >= 0; d--)
    {
        if (!isancestor(up[a][d], b))
        {
            a = up[a][d];
        }
    }
    return up[a][0];
}

int dist(int a, int b)
{
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

void solve()
{
    timer = 0;
    int n, q;
    cin >> n >> q;

    vvi adj(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    depth[0] = 0;
    dfs(0, 0, adj);
    Centroid cent(adj);
    vi cpar = cent.par;

    vi closest(n, inf);

    auto insert = [&](int u)
    {
        int v = u;
        while (v != -1)
        {
            closest[v] = min(closest[v], dist(u, v));
            v = cpar[v];
        }
    };
    insert(0);

    while (q--)
    {
        int t, u;
        cin >> t >> u;
        u--;
        if (t == 1)
        {
            insert(u);
        }
        else
        {
            int ans = inf;
            int v = u;
            while (v != -1)
            {
                ans = min(ans, closest[v] + dist(u, v));
                v = cpar[v];
            }
            cout << ans << "\n";
        }
    }
}

signed main()
{
    fast();

    int t;
    //cin >> t;
    t = 1;
    while (t--)
    {
        solve();
    }

    return 0;
}