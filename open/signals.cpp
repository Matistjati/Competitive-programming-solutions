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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Tree
{
    vi tree;
    Tree(int n) : tree(n*4, 0) {}

    void update(int x, int l, int r, int i, int v)
    {
        if (l==r)
        {
            tree[x] = max(tree[x],v);
        }
        else
        {
            int mid = (l + r) / 2;
            if (i <= mid) update(x * 2, l, mid, i, v);
            else update(x * 2 + 1, mid + 1, r, i, v);
            tree[x] = max(tree[x * 2], tree[x * 2 + 1]);
        }
    }

    int query(int x, int l, int r, int ql, int qr)
    {
        if (r < ql || l > qr) return 0;
        if (l >= ql && r <= qr) return tree[x];
        int mid = (l + r) / 2;
        return max(query(x * 2, l, mid, ql, qr), query(x*2+1,mid+1,r,ql,qr));
    }
};

signed main()
{
    fast();

    int n;
    cin >> n;

    vi dp(n, 1);
    Tree tree(n);
    rep(i, n)
    {
        int k;
        cin >> k;
        k--;
        
        dp[i] += tree.query(1, 0, n - 1, 0, k);
        tree.update(1, 0, n - 1, k, dp[i]);
    }
    cout << *max_element(all(dp));

    return 0;
}
