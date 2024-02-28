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

const int maxn = int(1.5e5);
int tin[maxn];
int tout[maxn];
int timer = 0;
int up[maxn][18];
bool upincreasing[maxn][18];
bool updecreasing[maxn][18];
int upmax[maxn][18];
int upmin[maxn][18];
int upv[maxn];

void dfs(int u, int p, int p1, int _p2, vector<vector<p2>>& edges)
{
    tin[u] = timer++;
    up[u][0] = p;
    upmax[u][0] = upv[u];
    upmin[u][0] = upv[u];
    upincreasing[u][0] = upmax[u][0] < upmax[p][0] || p == 0 || u == 0;
    updecreasing[u][0] = upmax[u][0] > upmax[p][0] || p == 0 || u == 0;
    repp(d, 1, 18)
    {
        int mid = up[u][d - 1];
        up[u][d] = up[mid][d - 1];
        upmax[u][d] = max(upmax[u][d - 1], upmax[mid][d - 1]);
        upmin[u][d] = min(upmin[u][d - 1], upmin[mid][d - 1]);
        upincreasing[u][d] = upincreasing[u][d - 1] && upincreasing[mid][d - 1] && (upmax[mid][0] < upmax[up[mid][0]][0] || up[mid][0] == 0 || mid == 0);
        updecreasing[u][d] = updecreasing[u][d - 1] && updecreasing[mid][d - 1] && (upmax[mid][0] > upmax[up[mid][0]][0] || up[mid][0] == 0 || mid == 0);
    }

    repe(e, edges[u]) if (e.first != p)
    {
        upv[e.first] = e.second;
        dfs(e.first, u, p1, _p2, edges);
    }

    tout[u] = timer++;
}

bool isancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int pathmax(int a, int b)
{
    if (isancestor(a, b)) return -1;
    int ret = -1;
    for (int d = 17; d >= 0; d--)
    {
        if (!isancestor(up[a][d], b))
        {
            ret = max(ret, upmax[a][d]);
            a = up[a][d];
        }
    }
    return max(ret, upmax[a][0]);
}

int pathmin(int a, int b)
{
    if (isancestor(a, b)) return inf;
    int ret = inf;
    for (int d = 17; d >= 0; d--)
    {
        if (!isancestor(up[a][d], b))
        {
            ret = min(ret, upmin[a][d]);
            a = up[a][d];
        }
    }
    return min(ret, upmin[a][0]);
}

int lca(int a, int b)
{
    if (isancestor(a, b)) return a;
    if (isancestor(b, a)) return b;
    for (int d = 17; d >= 0; d--)
    {
        if (!isancestor(up[a][d], b))
        {
            a = up[a][d];
        }
    }
    return up[a][0];
}

struct Centroid
{
    int n;
    vvi edges;
    vi vis;
    vi par;
    vi size;

    Centroid() {}
    Centroid(vvi& edges) : edges(edges), n(edges.size()), vis(n), par(n), size(n)
    {
        init_centroid(0, -1);
    }

    int find_centroid(int u, int p, int n)
    {
        repe(e, edges[u])
        {
            if (e == p) continue;
            if (!vis[e] && size[e] > n / 2) return find_centroid(e, u, n);
        }
        return u;
    }

    int find_size(int u, int p)
    {
        if (vis[u]) return 0;
        size[u] = 1;

        repe(e, edges[u])
        {
            if (e == p) continue;
            size[u] += find_size(e, u);
        }
        return size[u];
    }

    void init_centroid(int u, int p)
    {
        find_size(u, u);

        int c = find_centroid(u, u, size[u]);
        vis[c] = 1;
        par[c] = p;

        repe(e, edges[c])
        {
            if (!vis[e]) init_centroid(e, c);
        }
    }
};

struct fenwick
{
    vi tree;
    fenwick(int n) : tree(n + 1) {}

    void update(int i, int v)
    {
        for (i++; i < sz(tree); i += i & -i)
            tree[i] += v;
    }

    int query(int i)
    {
        int ret = 0;
        for (i++; i > 0; i -= i & -i)
            ret += tree[i];
        return ret;
    }
};

signed main()
{
    fast();

    //ifstream in("C:\\Users\\Matis\\desktop\\comp_prog\\x64\\debug\\in.txt");
    //cin.rdbuf(in.rdbuf());

    int n, q;
    cin >> n >> q;

    vvi queries;
    int t = 0;
    vector<vector<p2>> edges(n);
    vector<p2> edgelist;
    vvi e(n);
    rep(i, n + q - 1)
    {
        char c;
        cin >> c;
        if (c == 'S')
        {
            int a, b;
            cin >> a >> b;
            a--; b--;
            edgelist.push_back(p2(a, b));
            edges[a].push_back(p2(b, t));
            edges[b].push_back(p2(a, t));
            e[a].push_back(b);
            e[b].push_back(a);
            t++;
        }
        else if (c == 'Q')
        {
            int a, b;
            cin >> a >> b;
            a--; b--;
            queries.push_back({ 0, b, a, t - 1 });
        }
        else
        {
            int c;
            cin >> c;
            c--;
            queries.push_back({ 1, c, -1, t - 1 });
        }
    }
    dfs(0, 0, -1, -1, edges);
    Centroid cent(e);

    auto getmax = [&](int a, int b)
    {
        return max(pathmax(a, b), pathmax(b, a));
    };

    auto getmin = [&](int a, int b)
    {
        return min(pathmin(a, b), pathmin(b, a));
    };

    auto pathgood = [&](int a, int b, int t)
    {
        if (getmax(a, b) > t) return false;
        // all edges <= t
        // from b->lca increasing
        // from a->lca decreasing
        bool good = 1;
        int u = b;
        int prev = inf;
        for (int d = 17; d >= 0; d--)
        {
            if (!isancestor(up[u][d], a))
            {
                good &= updecreasing[u][d];
                u = up[u][d];
            }
        }
        if (!isancestor(u, a))
        {
            prev = upmax[u][0];
        }

        u = a;
        int v = -1;
        for (int d = 17; d >= 0; d--)
        {
            if (!isancestor(up[u][d], b))
            {
                good &= upincreasing[u][d];
                u = up[u][d];
            }
        }
        if (!isancestor(u, b))
        {
            v = upmax[u][0];
        }

        return good && (v < prev);
    };

    vector<fenwick> children(n, fenwick(0));
    vi centroidpar = cent.par;


    vector<vector<p2>> enableat(n + 2);
    vvi values(n);
    rep(i, n)
    {
        int u = centroidpar[i];
        while (u != -1)
        {
            if (pathgood(u, i, inf))
            {
                enableat[getmax(u, i)].emplace_back(u, getmin(i, u));
                values[u].push_back(getmin(i, u));
            }
            u = centroidpar[u];
        }
    }
    vector<map<int, int>> fenpos(n);
    rep(i, n)
    {
        set<int> cv(all(values[i]));
        int j = 0;
        repe(e, cv) fenpos[i][e] = j++;
        children[i] = fenwick(cv.size());
    }
    vi tot(n);

    int timer = 0;
    repe(q, queries)
    {
        int type = q[0], a = q[1], b = q[2], t = q[3];

        if (type == 0)
        {
            cout << (pathgood(a, b, t) ? "yes" : "no") << "\n";
        }
        else
        {

            while (timer <= t)
            {
                repe(e, enableat[timer])
                {
                    children[e.first].update(fenpos[e.first][e.second], 1);
                    tot[e.first]++;
                }
                timer++;
            }

            int ans = tot[a];
            int u = a;
            int prev = u;
            while (centroidpar[u] != -1)
            {
                prev = u;
                u = centroidpar[u];
                if (pathgood(a, u, t))
                {
                    ans++;
                    int v = getmax(a, u);
                    ans += tot[u];
                    int ind = sz(fenpos[u]);
                    auto it = fenpos[u].upper_bound(v);
                    if (it != fenpos[u].end()) ind = it->second;
                    if (ind) ans -= children[u].query(ind - 1);
                }
            }

            cout << ans + 1 << "\n";
        }
    }

    return 0;
}