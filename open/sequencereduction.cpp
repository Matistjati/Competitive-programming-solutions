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
    vi tree;
    Tree(int n) : tree(n*4) {}

    void update(int x, int l, int r, int i, int v)
    {
        if (l == r) return void(tree[x] = v);
        int mid = (l + r) / 2;
        if (i <= mid) update(x * 2, l, mid, i, v);
        else update(x * 2 + 1, mid + 1, r, i, v);
        tree[x] = max(tree[x * 2], tree[x * 2 + 1]);
    }
    int query(int x, int l, int r, int ql, int qr)
    {
        if (l >= ql && r <= qr) return tree[x];
        if (l > qr || r < ql) return 0;
        int mid = (l + r) / 2;
        return max(query(x * 2, l, mid, ql, qr), query(x * 2 + 1, mid + 1, r, ql, qr));
    }
};
Tree tree(0);
vector<p2> nums;

int ans(int l, int r, int n)
{
    if (l > r) return -1;
    int m=tree.query(1,0,n-1,l,r);

    vi occs;
    int lo = lower_bound(all(nums), p2(m,l)) - begin(nums);
    int hi = lower_bound(all(nums), p2(m,r+1))-begin(nums);
    repp(i, lo, hi) occs.push_back(nums[i].second);

    int ret = 0;
    int prev = l-1;
    repe(o, occs)
    {
        int re = ans(prev + 1, o - 1, n);
        if (re != -1) ret += re + m;
        prev = o;
    }
    int re = ans(prev + 1, r, n);
    if (re != -1) ret += re + m;
    ret += (sz(occs) - 1) * m;

    return ret;
}

signed main()
{
    fast();

    //ifstream in("e:/in.txt");
    //cin.rdbuf(in.rdbuf());

    int n;
    cin >> n;
    tree = Tree(n);
    nums.resize(n);
    rep(i, n) cin >> nums[i].first,nums[i].second=i;
    rep(i, n)
    {
        tree.update(1, 0, n - 1, i, nums[i].first);
    }
    sort(all(nums));


    cout << ans(0, n - 1, n);
    //cout << "";

    return 0;
}
