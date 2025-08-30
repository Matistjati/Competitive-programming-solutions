#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

void topsort(int u, vi & vis, vi & order, vvi & adj)
{
    if (vis[u]) return;
    vis[u] = 1;
    repe(e, adj[u]) topsort(e, vis, order, adj);
    order.push_back(u);
}

void dfs(int u, int comp, vi& whichcomp, vvi& adj)
{
    if (whichcomp[u] != -1) return;
    whichcomp[u] = comp;
    repe(e, adj[u]) dfs(e, comp, whichcomp, adj);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    vvi adj(n);
    vvi radj(n);
    vector<p2> edges;
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        radj[b].push_back(a);
        edges.emplace_back(a, b);
    }
    vi vis(n);
    vi order;
    rep(i, n) topsort(i, vis, order, radj);
    reverse(all(order));

    vi whichcomp(n,-1);
    int compind = 0;
    repe(u, order)
    {
        if (whichcomp[u] != -1) continue;
        dfs(u, compind++, whichcomp, adj);
    }
    vvi compmembers(compind);
    rep(i, n) compmembers[whichcomp[i]].push_back(i);
    vvi adj2(compind);
    vi compsize(compind);
    rep(i, n) compsize[whichcomp[i]]++;
    for (auto [a, b] : edges)
    {
        a = whichcomp[a];
        b = whichcomp[b];
        if (a != b) adj2[a].push_back(b);
    }
    vi dp(compind,-1);
    vi choice(compind,-1);
    auto dfs2 = [&](auto self, int u) -> int {
        if (dp[u] != -1) return dp[u];
        int ret = 0;
        repe(e, adj2[u])
        {
            int x = self(self, e);
            if (x>ret)
            {
                ret = x;
                choice[u] = e;
            }
        }
        ret += compsize[u];
        return dp[u]=ret;
    };
    rep(i, compind) dfs2(dfs2, i);
    cout << *max_element(all(dp)) << '\n';
    int start = max_element(all(dp)) - begin(dp);
    vi ans;
    int x = start;
    while (x!=-1)
    {
        ans.insert(ans.end(), all(compmembers[x]));
        x = choice[x];
    }
    repe(u, ans) cout << u+1 << " ";
    cout << '\n';
    cout << compmembers[start][0]+1 << '\n';

    return 0;
}
