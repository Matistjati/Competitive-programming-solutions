#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
//const int inf = int(1e18);
const int inf = int(1e9);

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
#define __builtin_clz _lzcnt_u32
#define assert(x) if (!(x)) __debugbreak()
#endif

constexpr int maxn = int(5e5 + 10);
int up[20][maxn];
int pmax[20][maxn];
int tin[maxn];
int tout[maxn];
int timer = 0;

void dfs2(int u, int p, int parweight, vi& lo, vector<vector<p2>>& adj)
{
    tin[u] = timer++;
    up[0][u] = p;
    pmax[0][u] = parweight;

    repp(d, 1, 20)
    {
        int upd = up[d - 1][u];
        up[d][u] = up[d - 1][upd];
        pmax[d][u] = max(pmax[d - 1][u], pmax[d - 1][upd]);
    }

    repe(e, adj[u])
    {
        if (e.first == p) continue;
        dfs2(e.first, u, lo[e.second], lo, adj);
    }

    tout[u] = timer++;
}

int isancestor(int a, int b)
{
    return tin[a] <= tin[b] && tin[b] <= tout[a];
}

int lca(int a, int b)
{
    if (isancestor(a, b)) return a;
    if (isancestor(b, a)) return b;
    for (int d = 19; d >= 0; d--)
    {
        if (!isancestor(up[d][a], b))
        {
            a = up[d][a];
        }
    }
    return up[0][a];
}

int upmax(int a, int b)
{
    assert(isancestor(b, a));

    int ret = -inf;
    for (int d = 19; d >= 0; d--)
    {
        if (!isancestor(up[d][a], b))
        {
            ret = max(ret, pmax[d][a]);
            a = up[d][a];
        }
    }
    return max(ret, pmax[0][a]);
}

int pathmax(int a, int b)
{
    assert(a != b);
    if (isancestor(a, b)) return upmax(b, a);
    if (isancestor(b, a)) return upmax(a, b);
    int l = lca(a, b);
    return max(upmax(a, l), upmax(b, l));
}


void solve()
{
    int n, m;
    cin >> n >> m;

    vi lo(m);
    vi hi(m);

    vector<vector<p2>> adj(n);
    vector<p2> edges;
    rep(i, m)
    {
        int a, b, l, r;
        cin >> a >> b >> l >> r;
        l--; r--;
        a--; b--;
        if (i < n - 1)
        {
            adj[a].emplace_back(b, i);
            adj[b].emplace_back(a, i);
        }
        lo[i] = l;
        hi[i] = r;
        edges.emplace_back(a, b);
    }
    dfs2(0, 0, -1, lo, adj);
    repp(i, n - 1, m)
    {
        lo[i] = max(lo[i], pathmax(edges[i].first, edges[i].second) + 1);
    }
    rep(i, 20) rep(j, n) pmax[i][j] = inf;

    auto set = [&](int a, int b, int v)
    {
        assert(!isancestor(a, b));
        for (int d = 19; d >= 0; d--)
        {
            if (!isancestor(up[d][a], b))
            {
                pmax[d][a] = min(pmax[d][a], v);
                a = up[d][a];
            }
        }
        pmax[0][a] = min(pmax[0][a], v);
    };

    auto apply = [&](int a, int b, int v)
    {
        if (isancestor(a, b)) return set(b, a, v);
        if (isancestor(b, a)) return set(a, b, v);
        int l = lca(a, b);
        set(a, l, v);
        set(b, l, v);
    };

    repp(i, n - 1, m)
    {
        int a, b;
        tie(a, b) = edges[i];

        apply(a, b, hi[i] - 1);
    }

    for (int d = 19; d >= 1; d--)
    {
        rep(i, n)
        {
            pmax[d - 1][i] = min(pmax[d - 1][i], pmax[d][i]);
            pmax[d - 1][up[d - 1][i]] = min(pmax[d - 1][up[d - 1][i]], pmax[d][i]);
        }
    }
    repp(i, 0, n - 1)
    {
        int a, b;
        tie(a, b) = edges[i];
        if (isancestor(a, b)) hi[i] = min(hi[i], pmax[0][b]);
        else if (isancestor(b, a)) hi[i] = min(hi[i], pmax[0][a]);
        else
        {
            hi[i] = min(hi[i], pmax[0][a]);
            hi[i] = min(hi[i], pmax[0][b]);
        }
    }


    vector<tuple<int, int, int>> intervals;
    rep(i, m)
    {
        intervals.emplace_back(lo[i], hi[i], i);
    }
    sort(all(intervals));

    bool good = 1;

    vi who(m, -1);
    priority_queue<p2> pq;
    int j = 0;
    rep(i, m)
    {
        while (j < sz(intervals) && get<0>(intervals[j]) <= i)
        {
            pq.emplace(-get<1>(intervals[j]), get<2>(intervals[j]));
            j++;
        }
        while (sz(pq) && -pq.top().first < i)
        {
            pq.pop();
        }
        if (pq.empty())
        {
            cout << "NO\n";
            return;
        }
        p2 p = pq.top();
        pq.pop();
        who[i] = p.second;
    }

    rep(i, m) good &= who[i] != -1;
    if (!good)
    {
        cout << "NO\n";
        return;
    }


    cout << "YES\n";
    vi edge_w(m);
    rep(i, m) edge_w[who[i]] = i;
    rep(i, m)
    {
        cout << edge_w[i] + 1 << " ";
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
