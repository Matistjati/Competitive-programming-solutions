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

struct Tree
{
    vi lset, ladd, sum;
    Tree(int n) : lset(n*4, inf), ladd(n*4), sum(n*4) {}

    void apply_set(int u, int l, int r, int s)
    {
        lset[u] = s;
        ladd[u] = 0;
        sum[u] = (r - l + 1) * s;
    }

    void apply_add(int u, int l, int r, int s)
    {
        if (lset[u] != inf) return apply_set(u, l, r, lset[u] + s);
        ladd[u] += s;
        sum[u] += (r - l + 1) * s;
    }

    void push_children(int x, int l, int r)
    {
        int mid = (l + r) / 2;
        if (lset[x]!=inf)
        {
            assert(ladd[x] == 0);
            apply_set(x * 2, l, mid, lset[x]);
            apply_set(x * 2+1, mid+1, r, lset[x]);
            lset[x] = inf;
        }
        if (ladd[x])
        {
            apply_add(x * 2, l, mid, ladd[x]);
            apply_add(x * 2+1, mid+1, r, ladd[x]);
            ladd[x] = 0;
        }
    }

    void range_add(int x, int l, int r, int ql, int qr, int s)
    {
        if (r < ql || l > qr) return;
        if (l>=ql&&r<=qr)
        {
            apply_add(x, l, r, s);
            return;
        }
        push_children(x, l, r);

        int mid = (l + r) / 2;
        range_add(x*2, l, mid, ql, qr, s);
        range_add(x*2+1, mid + 1, r, ql, qr, s);
        sum[x] = sum[x * 2] + sum[x * 2 + 1];
    }

    void range_set(int x, int l, int r, int ql, int qr, int s)
    {
        if (r < ql || l > qr) return;
        if (l >= ql && r <= qr)
        {
            apply_set(x, l, r, s);
            return;
        }
        push_children(x, l, r);

        int mid = (l + r) / 2;
        range_set(x*2, l, mid, ql, qr, s);
        range_set(x*2+1, mid + 1, r, ql, qr, s);
        sum[x] = sum[x * 2] + sum[x * 2 + 1];
    }

    int query(int x, int l, int r, int ql, int qr)
    {
        if (r < ql || l > qr) return 0;
        if (l >= ql && r <= qr) return sum[x];
        push_children(x, l, r);

        int mid = (l + r) / 2;
        return query(x*2, l, mid, ql, qr)+query(x*2+1, mid + 1, r, ql, qr);
    }
};

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    Tree tree(n);

    rep(i, n)
    {
        int v;
        cin >> v;
        tree.range_set(1, 0, n - 1, i, i, v);
    }
    while (q--)
    {
        int t,l,r;
        cin >> t >> l >> r;
        l--; r--;
        if (t==1)
        {
            int v;
            cin >> v;
            tree.range_add(1, 0, n - 1, l, r, v);
        }
        if (t==2)
        {
            int v;
            cin >> v;
            tree.range_set(1, 0, n - 1, l, r, v);
        }
        if (t==3)
        {
            cout << tree.query(1, 0, n - 1, l, r) << "\n";
        }
    }


    return 0;
}
