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

struct UF
{
    vi par;
    vi size;
    UF(int n) : par(n), size(n, 1)
    {
        rep(i, n) par[i] = i;
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        par[b] = a;
        size[a] += size[b];
    }
};

constexpr int maxn = int(1000);
int tin[maxn];
int tout[maxn];
int up[11][maxn];
int upmax[11][maxn];
int timer = 0;

void dfs(int u, int p, int pw, vector<vector<p2>>& adj)
{
    tin[u] = timer++;
    up[0][u] = p;
    upmax[0][u] = pw;
    repp(d, 1, 11)
    {
        int v = up[d - 1][u];
        up[d][u] = up[d - 1][v];
        upmax[d][u] = max(upmax[d - 1][u], upmax[d - 1][v]);
    }

    repe(e, adj[u]) if (e.first != p) dfs(e.first, u, e.second, adj);

    tout[u] = timer++;
}

int isancestor(int a, int b)
{
    return tin[a] <= tin[b] && tin[b] <= tout[a];
}

int up_max(int a, int b)
{
    assert(!isancestor(a, b));

    int ret = -inf;
    for (int d = 10; d >= 0; d--)
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
    assert(a != b);
    if (isancestor(a, b)) return up_max(b,a);
    if (isancestor(b, a)) return up_max(a, b);
    return max(up_max(a, b), up_max(b, a));
}

signed main()
{
    fast();

    int n, m;
    while (cin >> n >> m)
    {
        timer = 0;
        UF uf(n);
        vector<tuple<int, int, int>> edges;
        rep(i, m)
        {
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--;
            edges.emplace_back(c, a, b);
        }
        sort(all(edges));

        int ans = 0;
        int num_comps = n;
        vi tree_edge(m);
        int largest_tree = 0;
        vector<vector<p2>> adj(n);
        rep(i, m)
        {
            int c, a, b;
            tie(c, a, b) = edges[i];
            if (uf.find(a)!=uf.find(b))
            {
                tree_edge[i] = 1;
                uf.merge(a, b);
                ans += c;
                num_comps--;
                largest_tree = i;
                adj[a].emplace_back(b, c);
                adj[b].emplace_back(a, c);
            }
        }

        if (num_comps>1)
        {
            cout << "disconnected\n";
            continue;
        }
        dfs(0, 0, -inf, adj);
        int best_swap = 2*get<0>(edges[largest_tree]);
        repp(i, largest_tree + 1, m)
        {
            int c, a, b;
            tie(c, a, b) = edges[i];
            int k = c;
            k += pathmax(a, b);
            best_swap = max(best_swap, k);
        }
        cout << ans - best_swap << "\n";
    }

    return 0;
}
