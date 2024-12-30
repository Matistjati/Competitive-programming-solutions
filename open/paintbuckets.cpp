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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Tree
{
    vi tree;
    Tree(int n) : tree(n*4) {}

    void update(int x, int l, int r, int i, int v)
    {
        if (l == r) return void(tree[x] += v);
        int mid = (l + r) / 2;
        if (i <= mid) update(x * 2, l, mid, i, v);
        else update(x * 2 + 1, mid + 1, r, i, v);
        tree[x] = tree[x * 2] + tree[x * 2 + 1];
    }

    int query(int x, int l, int r, int ql, int qr)
    {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return tree[x];
        int mid = (l + r) / 2;
        return query(x * 2, l, mid, ql, qr) + query(x * 2 + 1, mid + 1, r, ql, qr);
    }
};

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;

    map<int, int> idx;
    vector<p2> stock;
    rep(i, n)
    {
        int h, v;
        cin >> h >> v;
        stock.emplace_back(h, v);
    }
    sort(all(stock));
    Tree tree(n);
    vi coords;
    repe(u, stock)
    {
        if (!idx.count(u.first)) idx[u.first] = sz(idx), coords.push_back(u.first);
        u.first = idx[u.first];
        tree.update(1, 0, n - 1, u.first, u.second);
    }
    
    while (q--)
    {
        int h, v;
        cin >> h >> v;

        int l = lower_bound(all(coords), h - 1000) - begin(coords);
        int r;
        auto it = upper_bound(all(coords), h + 1000);
        if (it != begin(coords)) r = prev(it) - begin(coords);
        else r = -1;
        int t = tree.query(1, 0, n - 1, l, r);
        cout << (t >= v ? "yes" : "no") << "\n";
    }

    return 0;
}
