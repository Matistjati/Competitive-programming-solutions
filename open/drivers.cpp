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

struct UF
{
    vi par;
    vi size;
    UF(int n) : par(n), size(n, 1)
    {
        rep(i, n)par[i] = i;
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
};

signed main()
{
    fast();

    int n, m, q;
    cin >> n >> m >> q;

    UF uf(n);

    vector<tuple<int, int, int>> edges;
    vector<tuple<int,int,int,int>> queries;
    rep(i, m)
    {
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        edges.emplace_back(w, a, b);
    }
    sort(all(edges));

    rep(i, q)
    {
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        queries.emplace_back(w, a, b, i);
    }
    sort(all(queries));

    int ind = 0;
    vi ans(q);
    rep(i, q)
    {
        auto [w, a, b, qind] = queries[i];
        while (ind<m&&get<0>(edges[ind]) <= w)
        {
            uf.merge(get<1>(edges[ind]), get<2>(edges[ind]));
            ind++;
        }
        ans[qind] = uf.find(a) == uf.find(b);
    }
    repe(u, ans) cout << (u ? "TAIP" : "NE") << '\n';

    return 0;
}
