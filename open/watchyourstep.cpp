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

void toposort(int u, vi& vis, vi& order, vvi& adj)
{
    if (vis[u]) return;
    vis[u] = 1;

    rep(e,sz(adj)) if(adj[u][e]) toposort(e, vis, order, adj);

    order.push_back(u);
}

void color(int u, int c, vi& nodecolor, vvi& adj)
{
    if (nodecolor[u] != -1) return;
    nodecolor[u] = c;
    rep(e, sz(adj)) if (adj[u][e]) color(e, c, nodecolor, adj);
}

signed main()
{
    fast();

    int n;
    cin >> n;
    vvi adj(n, vi(n));
    vvi radj(n, vi(n));
    rep(i, n) rep(j, n)
    {
        int x;
        cin >> x;
        adj[i][j] = x;
        radj[j][i] = x;
    }

    vi vis(n);
    vi order;
    rep(i, n) toposort(i, vis, order, radj);

    reverse(all(order));
    vi ncolor(n,-1);
    int cind = 0;
    repe(u, order)
    {
        if (ncolor[u] != -1) continue;
        color(u, cind++, ncolor, adj);
    }
    int ans = 0;

    rep(i, n)
    {
        rep(j, n)
        {
            if (i == j) continue;
            if (ncolor[j] <= ncolor[i] && !adj[i][j]) ans++;
        }
    }
    cout << ans;

    return 0;
}
