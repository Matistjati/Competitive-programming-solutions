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
    vi sum;
    vi lazysum;
    vi lazypoly;

    Tree(int n) : sum(n*4), lazysum(n*4), lazypoly(n*4) {}

    void set(int x, int l, int r, int i, int v)
    {
        if (l == r) sum[x] = v;
        else
        {
            int mid = (l + r) / 2;
            if (i <= mid) set(x * 2, l, mid, i, v);
            else set(x * 2 + 1, mid + 1, r, i, v);
            sum[x] = sum[x * 2] + sum[x * 2 + 1];
        }
    }

    void push(int x, int l, int r, int accum, int poly)
    {
        int numel = r - l + 1;
        sum[x] += poly * (numel * (numel + 1) / 2);
        sum[x] += numel * accum;
        lazysum[x] += accum;
        lazypoly[x] += poly;
    }

    void push_children(int x, int l, int r)
    {
        int mid = (l + r) / 2;
        push(x * 2, l, mid, lazysum[x], lazypoly[x]);
        push(x * 2 + 1, mid + 1, r, lazysum[x] + (mid - l + 1)*lazypoly[x], lazypoly[x]);

        lazysum[x] = 0;
        lazypoly[x] = 0;
    }

    int add(int x, int l, int r, int ql, int qr, int accum)
    {
        if (r < ql || l > qr) return 0;
        if (l>=ql&&r<=qr)
        {
            push(x, l, r, accum, 1);
            return r-l+1;
        }
        push_children(x, l, r);

        int mid = (l + r) / 2;
        int ret = add(x * 2, l, mid, ql, qr, accum);
        accum += ret;
        ret += add(x * 2 + 1, mid + 1, r, ql, qr, accum);
        sum[x] = sum[x * 2] + sum[x * 2 + 1];
        return ret;
    }

    int query(int x, int l, int r, int ql, int qr)
    {
        if (r < ql || l > qr) return 0;
        if (l >= ql && r <= qr) return sum[x];
        push_children(x, l, r);

        int mid = (l + r) / 2;
        return query(x * 2, l, mid, ql, qr) + query(x * 2 + 1, mid + 1, r, ql, qr);
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
        tree.set(1, 0, n - 1, i, v);
    }

    while (q--)
    {
        int t, l, r;
        cin >> t >> l >> r;
        l--; r--;
        if (t==1)
        {
            tree.add(1, 0, n - 1, l, r, 0);
        }
        else
        {
            cout << tree.query(1, 0, n - 1, l, r) << "\n";
        }
    }
    
    return 0;
}
