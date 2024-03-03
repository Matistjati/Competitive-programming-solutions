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
#define ceildiv(x,y) ((x + y - 1) / (y))

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


struct edge
{
    int w, a, b;
};

struct gedge
{
    int to, w, ind;
    bool operator==(const gedge& other) const {
        return (to == other.to && w == other.w && ind == other.ind);
    }
};

void markside(int u, int p, vector<vector<gedge>>& edges, vector<bool>& mark)
{
    mark[u] = 1;
    repe(e, edges[u]) if (e.to != p) markside(e.to, u, edges, mark);
}


bool pathmin(int u, int p, int t, vector<vector<gedge>>& edges, int& bestind, int& bestv)
{
    if (u == t) return 1;

    repe(e, edges[u])
    {
        if (e.to == p) continue;
        if (pathmin(e.to, u, t, edges, bestind, bestv))
        {
            if (e.w < bestv)
            {
                bestv = e.w;
                bestind = e.ind;
            }
            return 1;
        }
    }
    return 0;
}

signed main()
{
    fast();

    //ifstream in("C:\\users\\matis\\desktop\\comp_prog\\x64\\debug\\in.txt");
    //cin.rdbuf(in.rdbuf());

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int, int>> sedgelist;
    vector<edge> edgelist;
    vector<vector<gedge>> edges(n);

    rep(i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        sedgelist.emplace_back(c, a, b, i);
        edgelist.push_back(edge({ c, a, b }));
    }
    UF uf(n);
    sort(all(sedgelist));
    reverse(all(sedgelist));
    vi ingraph(m);
    rep(i, m)
    {
        int c, a, b, ind;
        tie(c, a, b, ind) = sedgelist[i];
        if (uf.find(a) != uf.find(b))
        {
            ingraph[ind] = 1;
            uf.merge(a, b);
            edges[a].emplace_back(gedge({ b, c, ind }));
            edges[b].emplace_back(gedge({ a, c, ind }));
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        char c;
        cin >> c;
        if (c == 'B')
        {
            int e;
            cin >> e;
            e--;
            int oldw = edgelist[e].w;
            cin >> edgelist[e].w;
            vector<bool> mleft(n);
            int c = edgelist[e].w;
            int a = edgelist[e].a;
            int b = edgelist[e].b;
            if (!ingraph[e])
            {
                continue;
            }
            markside(a, b, edges, mleft);

            int bestv = -inf;
            int bestind = -1;
            rep(i, m)
            {
                edge& e = edgelist[i];
                if ((mleft[e.a] ^ mleft[e.b]) == 1 && e.w > bestv)
                {
                    bestv = e.w;
                    bestind = i;
                }
            }

            if (ingraph[e])
            {
                edges[a].erase(find(all(edges[a]), gedge({ b, oldw, e })));
                edges[b].erase(find(all(edges[b]), gedge({ a, oldw, e })));
            }

            ingraph[e] = 0;
            int cc = edgelist[bestind].w;
            int l = edgelist[bestind].a;
            int r = edgelist[bestind].b;
            ingraph[bestind] = 1;
            edges[l].emplace_back(gedge({ r, cc, bestind }));
            edges[r].emplace_back(gedge({ l, cc, bestind }));
        }
        else if (c == 'R')
        {
            int e;
            cin >> e;
            e--;
            int oldw = edgelist[e].w;
            cin >> edgelist[e].w;
            int c = edgelist[e].w;
            int a = edgelist[e].a;
            int b = edgelist[e].b;
            if (ingraph[e])
            {
                auto it = find(all(edges[a]), gedge({ b, oldw, e }));
                it->w = c;
                it = find(all(edges[b]), gedge({ a, oldw, e }));
                it->w = c;
                continue;
            }
            int bestind = -1;
            int bestv = c;
            pathmin(a, a, b, edges, bestind, bestv);
            if (bestind != -1)
            {
                if (ingraph[bestind])
                {
                    int cc = edgelist[bestind].w;
                    int l = edgelist[bestind].a;
                    int r = edgelist[bestind].b;
                    edges[l].erase(find(all(edges[l]), gedge({ r, cc, bestind })));
                    edges[r].erase(find(all(edges[r]), gedge({ l, cc, bestind })));
                }

                ingraph[bestind] = 0;

                ingraph[e] = 1;
                edges[a].emplace_back(gedge({ b, c, e }));
                edges[b].emplace_back(gedge({ a, c, e }));
            }
        }
        else
        {
            int a, b, w;
            cin >> a >> b >> w;
            a--; b--;
            int bestind = -1;
            int bestv = inf;
            pathmin(a, a, b, edges, bestind, bestv);
            cout << (w <= bestv ? "1" : "0") << "\n";
        }
    }


    return 0;
}
