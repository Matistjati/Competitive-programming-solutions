#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

#define rep(i, b) for(ll i = 0; i < (b); i++)
#define repp(i, a, b) for(ll i = a; i < (b); i++)
#define repe(i,arr) for (auto& i : arr)
#define all(x) begin(x), end(x)
#define sz(x) ((ll)(x).size())
typedef pair<ll, ll> p2;
typedef vector<ll> vi;
typedef vector<vi> vvi;

struct Tree
{
    vi tree;
    Tree(ll n) : tree(n*4, 0) {}

    void update(ll x, ll l, ll r, ll i, ll v)
    {
        if (l == r) return void(tree[x] = max(tree[x],v));
        ll mid = (l + r) / 2;
        if (i <= mid) update(x * 2, l, mid, i, v);
        else update(x * 2 + 1, mid + 1, r, i, v);
        tree[x] = max(tree[x * 2], tree[x * 2 + 1]);
    }

    ll query(int x, int l, int r, int ql, int qr)
    {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return tree[x];
        int mid = (l + r) / 2;
        return max(query(x * 2, l, mid, ql, qr), query(x * 2 + 1, mid + 1, r, ql, qr));
    }
};

void solve()
{
    int n;
    cin >> n;

    vi nums(n);
    repe(v, nums) cin >> v;

    set<ll> snums(all(nums));
    map<ll, ll> remap;
    repe(v, snums) remap[v] = sz(remap);
    repe(v, nums) v = remap[v];
    
    Tree uptree(n);
    vi dpup(n);
    rep(i, n)
    {
        dpup[i] = uptree.query(1, 0, n - 1, 0, nums[i] - 1)+1;
        uptree.update(1, 0, n - 1, nums[i], dpup[i]);
    }
    Tree downtree(n);
    vi dpdown(n);
    for (ll i = n-1; i>=0;i--)
    {
        dpdown[i] = downtree.query(1, 0, n - 1, 0, nums[i] - 1)+1;
        downtree.update(1, 0, n - 1, nums[i], dpdown[i]);
    }
    ll ans = 0;
    rep(i, n)
    {
        if (dpdown[i] > 1 && dpup[i] > 1) ans = max(ans, dpdown[i] + dpup[i]-1);
    }

    cout << ans << "\n";
}

signed main()
{
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
