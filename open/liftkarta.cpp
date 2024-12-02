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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct UF
{
    vi par;
    vi size;
    UF(int n) : par(n), size(n, 1)
    {
        rep(i, n) par[i] = i;
    }

    int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
};

const int maxn = int(1e5);
int up[18][maxn];
int upmax[18][maxn];
int tin[maxn];
int tout[maxn];
int timer = 0;

void dfs(int u, int p, int pm, vector<vector<p2>>& edges)
{
    tin[u] = timer++;
    up[0][u] = p;
    upmax[0][u] = pm;

    repp(d, 1, 18)
    {
        int mid = up[d - 1][u];
        up[d][u] = up[d - 1][mid];
        upmax[d][u] = max(upmax[d - 1][u], upmax[d - 1][mid]);
    }


    repe(e, edges[u]) if (e.first != p) dfs(e.first, u, e.second, edges);
    tout[u] = timer++;
}

bool isancestor(int a, int b)
{
    return tin[a] <= tin[b] && tin[b] <= tout[a];
}

int max_up(int a, int b)
{
    // jump from a to b
    if (isancestor(a, b)) return -inf;

    int ret = -inf;

    for (int d = 17; d >= 0; d--)
    {
        if (!isancestor(up[d][a], b))
        {
            ret = max(ret, upmax[d][a]);
            a = up[d][a];
        }
    }

    return max(ret, upmax[0][a]);
}

int pathmax(int a, int b)
{
    return max(max_up(a, b), max_up(b, a));
}

signed main()
{
    fast();

    int n, m, q;
    cin >> n >> m >> q;
    vector<tuple<int,int,int>> edges;

    rep(i, m)
    {
        int a, b, s;
        cin >> a >> b >> s;
        a--; b--;
        edges.emplace_back(s, a, b);
    }
    sort(all(edges));

    UF uf(n);
    vector<vector<p2>> adj(n);
    rep(i, m)
    {
        int s, a, b;
        tie(s, a, b) = edges[i];
        if (uf.find(a)!=uf.find(b))
        {
            uf.merge(a, b);
            adj[a].emplace_back(b, s);
            adj[b].emplace_back(a, s);
        }
    }

    dfs(0, 0, -inf, adj);

    rep(i, q)
    {
        int a, b, f, k, s;
        cin >> a >> b >> f >> k >> s;
        a--; b--;
        int m = pathmax(a, b); 
        int cannot = ceil(((double)(m-s))/( (double)k));
        int cnt = min(f, max(f-cannot, 0LL));

        cout << cnt << "\n";
    }

    return 0;
}

