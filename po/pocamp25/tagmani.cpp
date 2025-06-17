// O((N+K)logNlogK)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef uint32_t tempint;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

vector<vector<p2>> adj;

struct centroid
{
    vi par;
    vector<vi> par_dist;
    vi size;
    centroid() : par(sz(adj)), par_dist(sz(adj)), size(sz(adj))
    {
        init_centroid(0, -1);
    }

    void calc_sz(int u, int p)
    {
        size[u] = 1;
        repe(e, adj[u]) if (e.first != p) calc_sz(e.first, u), size[u] += size[e.first];
    }

    int find_centroid(int u, int p, int n)
    {
        repe(e, adj[u]) if (e.first != p && size[e.first] > n / 2) return find_centroid(e.first, u, n);
        return u;
    }

    void calc_dist(int u, int p, int d)
    {
        par_dist[u].emplace_back(d);
        repe(e, adj[u]) if (e.first != p) calc_dist(e.first, u, d + e.second);
    }

    void init_centroid(int u, int p)
    {
        calc_sz(u, -1);
        u = find_centroid(u, -1, size[u]);
        calc_dist(u, -1, 0);
        par[u] = p;
        repe(e, adj[u])
        {
            auto it = adj[e.first].begin();
            while (it->first != u) it = next(it);
            adj[e.first].erase(it);
            init_centroid(e.first, u);
        }
    }
};

const int lomask = (1 << 20) - 1;

struct fenwick
{
    int n;
    vector<int> tree;
    fenwick(int n) : n(n), tree(n + 1) {}
    fenwick() {}

    void update(int r, int v)
    {
        r = n - 1 - r;
        for (r++; r < sz(tree); r += (r & -r))
        {
            tree[r] = max(tree[r], v);
        }
    }

    int query(int l) // query [l, n)
    {
        int ret = 0;
        int r = n - 1 - l;
        for (r++; r > 0; r -= (r & -r))
        {
            ret = max(ret, tree[r]);
        }
        return ret;
    }
};

signed main()
{
    fast();

    int n, k;
    cin >> n >> k;
    adj.resize(n);
    rep(i, n - 1)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    vector<tuple<int, int, int, int>> trains;
    rep(i, k)
    {
        int a, b, t, d;
        cin >> a >> b >> t >> d;
        a--; b--;
        trains.emplace_back(t + d, a, b, d);
    }

    sort(all(trains));
    reverse(all(trains));

    centroid decomp;

    vi par = decomp.par;
    vvi& par_dist = decomp.par_dist;
    rep(i, n) reverse(all(par_dist[i]));
    vi unique_values(n);
    vvi values(n);

    auto add_nodes = [&](int u, int t)
    {
        int c = u;
        int i = 0;
        while (c != -1)
        {
            unique_values[c]++;
            values[c].push_back(t - par_dist[u][i]);
            c = par[c];
            i++;
        }
    };

    repe(tr, trains)
    {
        int t, a, b, d;
        tie(t, a, b, d) = tr;

        add_nodes(a, t - d);
    }
    add_nodes(0, inf);
    rep(i, n) sort(all(values[i]));

    vector<fenwick> trees(n);
    rep(i, n)
    {
        trees[i] = fenwick(unique_values[i]);
    }

    auto add = [&](int u, int t, int dpv)
    {
        int c = u;
        int i = 0;
        while (c != -1)
        {
            int realt = t - par_dist[u][i];
            int ind = lower_bound(all(values[c]), realt) - values[c].begin();
            trees[c].update(ind, dpv);
            c = par[c];
            i++;
        }
    };

    auto query = [&](int u, int t)
    {
        int ret = -inf;
        int c = u;
        int i = 0;
        while (c != -1)
        {
            int realt = t + par_dist[u][i];
            int ind = lower_bound(all(values[c]), realt) - values[c].begin();

            if (ind != unique_values[c]) ret = max(ret, trees[c].query(ind));

            c = par[c];
            i++;
        }
        return ret;
    };

    add(0, inf, 0);

    repe(tr, trains)
    {
        int t, a, b, d;
        tie(t, a, b, d) = tr;

        int best = query(b, t);

        if (best >= 0)
        {
            add(a, t - d, best + 1);
        }

    }

    rep(i, n)
    {
        cout << query(i, 0) << " ";
    }
    cout << endl;


    return 0;
}
