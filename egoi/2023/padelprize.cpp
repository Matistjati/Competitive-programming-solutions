#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

void dfs(int u, int mostcommon, vi& ans, vi& cnt, vvi& children, vector<p2>& nodeinfo)
{
    if (nodeinfo[u].second==-1)
    {
        ans[mostcommon]++;
        return;
    }

    if (nodeinfo[u].second!=-2)
    {
        int g = nodeinfo[u].first;
        cnt[g] += nodeinfo[u].second;
        if (cnt[g] > cnt[mostcommon] || (cnt[g] == cnt[mostcommon] && g < mostcommon)) mostcommon = g;
    }
    repe(c, children[u])
    {
        dfs(c, mostcommon, ans, cnt, children, nodeinfo);
    }
    if (nodeinfo[u].second != -2)
    {
        int g = nodeinfo[u].first;
        cnt[g] -= nodeinfo[u].second;
    }
}

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;

    vi whichnode(n, -1);

    vector<p2> nodes;
    vvi adj;

    rep(i, m)
    {
        int a, b;
        cin >> a >> b;

        nodes.emplace_back(-1, -1);
        adj.push_back({});

        nodes.emplace_back(a, i);
        adj.push_back({});
        adj.back().push_back(sz(adj) - 2);
        if (whichnode[a] != -1)
        {
            nodes[whichnode[a]].second = i - nodes[whichnode[a]].second;
            adj.back().push_back(whichnode[a]);
        }
        whichnode[a] = sz(adj)-1;

        if (whichnode[b] != -1)
        {
            nodes[whichnode[b]].second = i - nodes[whichnode[b]].second;
            adj.back().push_back(whichnode[b]);
            whichnode[b] = -1;
        }
    }

    nodes.emplace_back(-2, -2);
    adj.push_back({});
    rep(i, n)
    {
        if (whichnode[i] != -1)
        {
            nodes[whichnode[i]].second = m - nodes[whichnode[i]].second;
            adj.back().push_back(whichnode[i]);
        }
    }

    vi nummedals(n);
    vi ans(n);
    dfs(sz(adj) - 1, 0, ans, nummedals, adj, nodes);

    repe(cnt, ans) cout << cnt << " ";

    return 0;
}
