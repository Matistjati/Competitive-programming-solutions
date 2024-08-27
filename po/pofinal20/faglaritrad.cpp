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


int compsz(int u, int p, vvi& edges)
{
    int ret = 1;
    repe(e, edges[u]) if (e != p) ret += compsz(e, u, edges);
    return ret;
}

const int maxn = int(1e5);
int taken[maxn];
int start = -1;
int par[maxn];

int m;
int num_birds = 1;
void dfs(int u, int p, vvi& edges)
{
    if (num_birds == m) return;
    par[u] = p;
    taken[u] = 1;
    start = u;
    num_birds++;

    repe(e, edges[u]) if (e != p) dfs(e, u, edges);
}

bool ancestor_to_start[maxn];
void post(int u, int p, vi& order, vvi& edges)
{
    if (!taken[u]) return;

    order.push_back(u);
    vector<p2> adj;
    repe(e, edges[u])
    {
        if (e == p || !taken[e]) continue;
        adj.emplace_back(ancestor_to_start[e], e);
    }
    // first do all subtrees, then at the end go towards goal
    sort(all(adj));

    repe(e, adj)
    {
        post(e.second, u, order, edges);
    }
}

signed main()
{
    fast();

    int n, k;
    cin >> n >> m >> k;
    k--;

    vvi edges(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    repe(e, edges[k])
    {
        if (compsz(e, k, edges) + 1 < m) continue;
        dfs(e, k, edges);

        // mark all nodes path of start -> k
        int v = start;
        while (v != k)
        {
            ancestor_to_start[v] = 1;
            v = par[v];
        }

        vi order;
        post(start, start, order, edges);
        order.push_back(k);

        repe(u, order) cout << u + 1 << " ";
        return 0;
    }
    cout << -1;

    return 0;
}
