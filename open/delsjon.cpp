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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    int k;
    cin >> k;
    vvi dist(k, vi(k));
    rep(i, k)
    {
        rep(j, k)
        {
            int v;
            cin >> v;
            dist[i][j] = v;
        }
    }

    auto depth = [&](int u)
        {
            return dist[0][u];
        };
    vector<p2> edges;
    int ind = k;

    vi par(k + 1);

    auto addedge = [&](int a, int b) // a is deeper
        {
            par[a] = b;
            edges.emplace_back(a, b);
        };

    int last = 1;
    rep(i, dist[0][1] - 1)
    {
        addedge(last, ind);
        last = ind;
        ind++;
        par.push_back(0);
    }
    addedge(last, 0);

    repp(i, 2, k)
    {
        int d = 0;
        int bestd = 0;

        repp(j, 1, i)
        {
            assert((depth(i) + depth(j) - dist[i][j]) % 2 == 0);
            int lca_depth = (depth(i) + depth(j) - dist[i][j]) / 2;
            if (lca_depth > d)
            {
                d = lca_depth;
                bestd = j;
            }
        }
        int lca = bestd;
        rep(j, depth(bestd) - d) lca = par[lca];
        int last = i;
        rep(j, depth(i) - d - 1)
        {
            addedge(last, ind);
            last = ind++;
            par.push_back(0);
        }
        addedge(last, lca);
    }

    cout << ind << "\n";
    repp(i, 1, ind)
    {
        p2 e = p2(i, par[i]);
        cout << e.first + 1 << " " << e.second + 1 << "\n";
    }

    return 0;
}
