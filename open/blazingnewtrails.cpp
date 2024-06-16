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
#define __builtin_popcountll popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

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

    int n, m, k, w;
    cin >> n >> m >> k >> w;
    vi is_special(n);
    rep(i, k)
    {
        int u;
        cin >> u;
        is_special[u - 1] = 1;
    }

    typedef tuple<double, int, int, int> p4;
    typedef tuple<double, int, int> p3;
    vector<p3> edgesin;
    rep(i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        edgesin.emplace_back(a, b, c);
    }

    auto alien = [&](double mid)
    {
        vector<p4> edges;
        rep(j, m)
        {
            int a, b, c;
            tie(a, b, c) = edgesin[j];
            int special = is_special[a] != is_special[b];
            edges.emplace_back(c - special * mid, a, b, special);
        }
        sort(all(edges));
        UF uf(n);
        int numspecial = 0;
        double cost = 0;
        int comps = n;
        rep(i, m)
        {
            double c;
            int a, b, s;
            tie(c, a, b, s) = edges[i];
            if (uf.find(a)!=uf.find(b))
            {
                comps--;
                uf.merge(a, b);
                cost += c;
                numspecial += s;
            }
        }

        if (comps > 1) numspecial -= 1000000;
        return make_pair(cost,numspecial);
    };
    if (alien(10000000).second<w)
    {
        cout << "-1";
        return 0;
    }

    double lo = -1e6;
    double hi = 1e6;
    rep(i, 70)
    {
        double mid = (hi + lo) / 2;

        pair<double, int> r = alien(mid);
        if (r.second < w) lo = mid;
        else hi = mid;
    }
    cout << int(round(alien(hi).first + hi * w));

    return 0;
}
