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

const int maxn = int(2e5);
int depth[maxn];

void dfs(int u, int p, vvi& edges)
{
    depth[u] = depth[p] + 1;

    repe(e, edges[u])
    {
        if (e == p) continue;
        dfs(e, u, edges);
    }
}

void solve()
{
    int n, w;
    cin >> n >> w;

    vvi edges(n);
    vi par(n);
    vi par_ind(n);
    vi num_edges(n);
    vvi which_nodes(n);
    rep(i, n - 1)
    {
        int p;
        cin >> p;
        p--;
        par[i + 1] = p;
        par_ind[i + 1] = i;
        edges[i + 1].emplace_back(p);
        edges[p].emplace_back(i + 1);
    }
    depth[0] = -1;
    dfs(0, 0, edges);
    rep(i, n)
    {
        int a = i;
        int b = (i + 1) % n;
        if (depth[b]==depth[a]+1)
        {
            num_edges[a] = 1;
            which_nodes[par_ind[b]].push_back(a);
        }
        else
        {
            if (b!=0)
            {
                num_edges[a]++;
                which_nodes[par_ind[b]].push_back(a);
            }
            int t = par[b];
            int u = a;
            while (u!=t)
            {
                num_edges[a]++;
                which_nodes[par_ind[u]].push_back(a);
                u = par[u];
            }
        }
    }

    int ans = 0;
    int num_nonzero = n;
    rep(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        u-=2;
        ans += 2 * v;
        w -= v;
        repe(a, which_nodes[u])
        {
            num_edges[a]--;
            if (num_edges[a] == 0) num_nonzero--;
        }
        
        cout << ans + num_nonzero*w << " ";
    }
    cout << "\n";
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
