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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Tree
{
    vi tree;
    Tree(int n) : tree(n*4, 0) {}

    void update(int x, int l, int r, int ql, int qr, int v)
    {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr)
        {
            tree[x] = max(tree[x], v);
            return;
        }
        int mid = (l + r) / 2;
        update(x * 2, l, mid, ql, qr, v);
        update(x * 2 + 1, mid + 1, r, ql, qr, v);
    }

    int query(int x, int l, int r, int i)
    {
        if (l == r) return tree[x];
        int mid = (l + r) / 2;
        if (i <= mid) return max(tree[x], query(x * 2, l, mid, i));
        return max(tree[x], query(x*2+1,mid+1,r,i));
    }
};

signed main()
{
    fast();

    int n, k;
    cin >> n >> k;
    int s = n * k;
    vi a(s);
    vi b(s);
    rep(i, s) cin >> a[i];
    rep(i, s) cin >> b[i];

    map<int, vi> occs;
    rep(i, s) occs[a[i]].push_back(i);

    vvi arrows(s);
    rep(i, s)
    {
        int v = b[i];
        repe(u, occs[v])
        {
            arrows[i].push_back(u);
        }
    }

    Tree dp(s + 1);

    rep(i, s)
    {
        vi& arrow = arrows[i];
        sort(arrow.rbegin(), arrow.rend());
        repe(a, arrow)
        {
            int v = dp.query(1, 0, s, a) + 1;
            dp.update(1, 0, s, a + 1, s, v);
        }
    }
    int ans = 0;
    rep(i, s + 1) ans = max(ans, dp.query(1, 0, s, i));
    cout << ans;

    return 0;
}
