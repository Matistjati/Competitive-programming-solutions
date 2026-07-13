#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

struct Tree
{
    ll n;
    const ll unit = 0;
    vi tree;
    Tree(ll n) : n(n), tree(n * 4, unit) {}

    ll merge(ll a, ll b)
    {
        return a + b;
    }

    void update(ll x, ll l, ll r, ll i, ll v)
    {
        if (l == r) tree[x] = v;
        else
        {
            ll mid = (l + r) / 2;
            if (i <= mid) update(x * 2, l, mid, i, v);
            else update(x * 2 + 1, mid + 1, r, i, v);
            tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
        }
    }

    void update(ll i, ll v) { update(1, 0, n - 1, i, v); }

    ll query(ll x, ll l, ll r, ll ql, ll qr)
    {
        if (l > qr || r < ql) return unit;
        if (l >= ql && r <= qr) return tree[x];

        ll mid = (l + r) / 2;
        return merge(query(x * 2, l, mid, ql, qr), query(x * 2 + 1, mid + 1, r, ql, qr));
    }

    ll query(ll ql, ll qr) { return query(1, 0, n - 1, ql, qr); }
};

ll solve(const vi& flowersin)
{
    // Kinda ugly, but I can't be bothered
    set<p2> flowers;
    ll n = flowersin.size();
    rep(i, n) flowers.insert(p2(i, flowersin[i]));

    vi cnt(2e5 + 10);
    vvi locs(2e5 + 10);

    rep(i, n)
    {
        cnt[flowersin[i]]++;
        locs[flowersin[i]].push_back(i);
    }

    Tree tree(n);
    ll ans = 0;
    ll i = 0;
    while (flowers.size())
    {
        p2 v = *flowers.begin();
        if (cnt[v.second] == 1)
        {
            if (flowers.size() == 1)
            {
                break;
            }
            else
            {
                flowers.erase(v);
                p2 next = *flowers.begin();
                flowers.erase(next);
                flowers.insert(p2(next.first, v.second));
                flowers.insert(p2(v.first, next.second));
                ans++;
                continue;
            }
        }
        flowers.erase(v);

        ll j = locs[v.second].back();
        locs[v.second].pop_back();
        ans += n - 1 - j - tree.query(j, n - 1);
        tree.update(j, 1);
        flowers.erase(p2(j, v.second));

        cnt[v.second] -= 2;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, k;
    cin >> n >> k;

    vector<ll> flowers(n);
    for (auto& v : flowers) cin >> v;
    ll ans = solve(flowers);

    cout << ans << '\n';

    return 0;
}
