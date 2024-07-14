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
#define __builtin_clz 
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Tree
{
    vi tree;
    Tree(int n) : tree(n*4) {}

    void update(int x, int l, int r, int i, int v)
    {
        if (l == r) tree[x] += v;
        else
        {
            int mid = (l + r) / 2;
            if (i <= mid) update(x * 2, l, mid, i, v);
            else update(x * 2 + 1, mid + 1, r, i, v);
            tree[x] = tree[x * 2] + tree[x * 2 + 1];
        }
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

    int n;
    cin >> n;
    vi nums(n);
    rep(i, n) cin >> nums[i], nums[i]--;

    Tree ltree(n);
    vi lcnt(n);
    rep(i, n)
    {
        lcnt[i] = ltree.query(1, 0, n - 1, nums[i] + 1, n - 1);
        ltree.update(1, 0, n - 1, nums[i], 1);
    }
    
    Tree rtree(n);
    vi rcnt(n);
    for (int i = n-1; i >= 0; i--)
    {
        rcnt[i] = rtree.query(1, 0, n - 1, 0, nums[i] - 1);
        rtree.update(1, 0, n - 1, nums[i], 1);
    }

    int ans = 0;
    rep(i, n) ans += lcnt[i] * rcnt[i];
    cout << ans;

    return 0;
}
