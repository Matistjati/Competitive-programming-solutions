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

struct UF
{
    vi par;
    vi size;
    vi ind;
    UF(int n) : par(n), size(n, 1),ind(n)
    {
        rep(i, n)par[i] = i;
        rep(i, n)ind[i] = i;
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
};

bool dfs(int u, vi& mated, vi& vis, vvi& adj)
{
    if (vis[u]) return false;
    vis[u] = 1;
    if (mated[u] == -1) return true;
    int l = mated[u];
    repe(e, adj[l])
    {
        if (dfs(e,mated,vis,adj))
        {
            mated[e] = l;
            return true;
        }
    }
    return false;
}

signed main()
{
    fast();

    int n,m;
    cin >> n >> m;

    vector<string> grid(n);
    rep(i, n) cin >> grid[i];

    UF uf(n * m);
    vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
    rep(i, n) rep(j, m)
    {
        repe(dir, dirs)
        {
            p2 np = p2(i + dir.first, j + dir.second);
            if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= m) continue;
            if (grid[i][j] != grid[np.first][np.second]) continue;
            uf.merge(i * m + j, np.first * m + np.second);
        }
    }

    map<int, int> remap;
    rep(i, n* m)
    {
        int p = uf.ind[uf.find(i)];
        if (!remap.count(p)) remap[p] = sz(remap);
    }

    set<int> border;
    rep(i, m) border.insert(uf.ind[uf.find(i)]), border.insert(uf.ind[uf.find((n - 1)* m + i)]);
    rep(i, n) border.insert(uf.ind[uf.find(i*m)]), border.insert(uf.ind[uf.find(i*m+m-1)]);

    int cnode = 0;

    vvi adj(sz(remap)+sz(border)+1);

    set<p2> edges;
    rep(i, n) rep(j, m)
    {
        if (grid[i][j] != '0') continue;
        repe(dir, dirs)
        {
            p2 np = p2(i + dir.first, j + dir.second);
            if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= m) continue;
            if (grid[i][j] == grid[np.first][np.second]) continue;
            int u = remap[uf.find(i * m + j)];
            int v = remap[uf.find(np.first * m + np.second)];
            edges.insert(p2(u, v));
        }
    }

    int p = sz(remap);
    repe(u, border)
    {
        if (grid[u / m][u % m] == '0')
        {
            edges.emplace(remap[u], p++);
        }
        else
        {
            edges.emplace(p++, remap[u]);
        }
    }


    repe(e, edges)
    {
        adj[e.first].push_back(e.second);
    }

    int ans = 0;

    vi mated(sz(adj), -1);
    rep(i, sz(adj))
    {
        if (sz(adj[i]) == 0) continue;
        vi vis(sz(adj));
        repe(e, adj[i])
        {
            if (dfs(e, mated,vis,adj))
            {
                mated[e] = i;
                ans++;
                break;
            }
        }
    }

    cout << ans;

    return 0;
}
