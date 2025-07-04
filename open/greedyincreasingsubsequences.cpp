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

struct Tree
{
    vector<p2> tree;
    Tree(int n) : tree(n*4, p2(-1,-1)) {}

    void update(int x, int l, int r, int i, int v)
    {
        if (l == r) return void(tree[x] = p2(v, -i));
        int mid = (l + r) / 2;
        if (i <= mid) update(x * 2, l, mid, i, v);
        else update(x * 2 + 1, mid + 1, r, i, v);
        tree[x] = max(tree[x * 2], tree[x * 2 + 1]);
    }
    p2 walk(int x, int l, int r, int v)
    {
        if (l == r) return (tree[x].first>v ? tree[x] : p2(-1,-1));
        int mid = (l + r) / 2;
        if (tree[x * 2].first > v) return walk(x * 2, l, mid, v);
        return walk(x * 2 + 1, mid + 1, r, v);
    }
    p2 query(int x, int l, int r, int ql, int qr, int v)
    {
        if (l > qr || r < ql) return p2(-1, -1);
        if (l >= ql && r <= qr)
        {
            return walk(x,l,r,v);
        }
        int mid = (l + r) / 2;
        p2 lr = query(x * 2, l, mid, ql, qr, v);
        if (lr.first != -1) return lr;
        return query(x * 2 + 1, mid + 1, r, ql, qr, v);
    }
};

signed main()
{
    fast();

    int n;
    cin >> n;
    vi nums(n);
    repe(v, nums) cin >> v;

    Tree tree(n);
    rep(i, n) tree.update(1, 0, n - 1, i, nums[i]);

    vvi ans;
    while (1)
    {
        int v = -1;
        int ind = -1;
        vi arr;

        while (1)
        {
            p2 nxt = tree.query(1, 0, n - 1, ind + 1, n - 1, v);
            nxt.second = -nxt.second;
            if (nxt.first == -1) break;
            arr.push_back(nxt.first);
            tree.update(1, 0, n - 1, nxt.second, -1);
            ind = nxt.second;
            v = nxt.first;
        }

        if (sz(arr)) ans.push_back(arr);
        else break;
    }
    cout << sz(ans) << "\n";
    repe(u, ans)
    {
        repe(v, u) cout << v << " ";
        cout << "\n";
    }

    return 0;
}
