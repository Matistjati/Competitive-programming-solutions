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
        a = find(a), b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
};

signed main()
{
    fast();

#if _LOCAL
    ifstream in("e://in.txt");
    cin.rdbuf(in.rdbuf());
#endif
    int n, w;
    cin >> n >> w;


    vvi b(n, vi(n, inf));
    vvi c(n, vi(n, inf));
    rep(i, n - 1)
    {
        rep(j, i + 1)
        {
            int cap;
            cin >> cap;
            c[i + 1][j] = cap;
            c[j][i + 1] = cap;
        }
    }
    rep(i, n - 1)
    {
        rep(j, i + 1)
        {
            int cap;
            cin >> cap;
            b[i + 1][j] = cap;
            b[j][i + 1] = cap;
        }
    }

    vector<tuple<int, int, int>> edges;
    rep(i, n) rep(j, n)
    {
        if (i == j) continue;

        if (w-c[i][j] <= b[i][j]) edges.emplace_back(i, j, c[i][j]);
    }
    
    sort(all(edges), [](tuple<int, int, int> a, tuple<int, int, int> b)
        {
            return get<2>(a) > get<2>(b);
        });

    vector<tuple<int, int, int>> mst;
    UF uf(n);
    for (auto [u, v, weight] : edges)
    {
        if (uf.find(u)!=uf.find(v))
        {
            uf.merge(u, v);
            mst.emplace_back(u, v, w-weight);
        }
    }

    edges = vector<tuple<int, int, int>>();
    rep(i, n) rep(j, n)
    {
        if (i == j) continue;
        if (w-c[i][j] <= b[i][j]) edges.emplace_back(i, j, b[i][j]);
    }

    sort(all(edges), [](tuple<int, int, int> a, tuple<int, int, int> b)
        {
            return get<2>(a) > get<2>(b);
        });

    uf = UF(n);
    for (auto [u, v, weight] : edges)
    {
        if (uf.find(u) != uf.find(v))
        {
            uf.merge(u, v);
            mst.emplace_back(u, v, weight);
        }
    }

    auto wmat = [&](vector<vector<p2>>& adj)
        {
            vvi mat(n, vi(n, inf));
            rep(i, n)
            {
                vi vis(n);
                priority_queue<p2> pq;
                pq.emplace(inf, i);
                while (sz(pq))
                {
                    int w, u;
                    tie(w, u) = pq.top();
                    pq.pop();
                    if (vis[u]) continue;
                    vis[u] = 1;
                    mat[i][u] = w;

                    repe(e, adj[u]) pq.emplace(min(w, e.second), e.first);
                }
            }
            return mat;
        };

    auto testsol = [&](vector<tuple<int, int, int>> edges)
        {
            vector<vector<p2>> bikeadj(n), caradj(n);
            for (auto [u, v, weight] : edges)
            {
                bikeadj[u].emplace_back(v, weight);
                bikeadj[v].emplace_back(u, weight);

                caradj[u].emplace_back(v, w - weight);
                caradj[v].emplace_back(u, w - weight);
            }

            vvi dbike = wmat(bikeadj);
            bool ret = dbike == b;
            vvi cmat = wmat(caradj);
            ret &= cmat == c;
            return ret;
        };

    if (testsol(mst))
    {
        cout << sz(mst) << "\n";
        for (auto [u, v, weight] : mst)
        {
            cout << u << " " << v << " " << weight << "\n";
        }
    }
    else
    {
        cout << "NO";
    }


    return 0;
}
