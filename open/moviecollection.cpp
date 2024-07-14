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
        if (l == r) tree[x] = v;
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



    int t;
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        int tsz = n + q+5;
        Tree tree(tsz);
        vi pos(n);
        rep(i, n) pos[i] = i + q+1;
        rep(i, n) tree.update(1, 0, tsz-1, q+i+1, 1);
        
        int ind = q;
        while (q--)
        {
            int p;
            cin >> p;
            p--;
            cout << tree.query(1, 0, tsz - 1, 0, pos[p]-1) << " ";
            tree.update(1, 0, tsz - 1, pos[p], 0);
            pos[p] = ind;
            tree.update(1, 0, tsz - 1, ind, 1);
            ind--;
        }
        cout << "\n";
    }

    return 0;
}
