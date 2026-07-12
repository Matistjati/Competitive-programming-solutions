#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;

#define rep(i, b) for (ll i = 0; i < (b); ++i)
#define repp(i, a, b) for (ll i = (a); i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) ((ll)(x).size())

struct UF {
    vi e;
    UF(ll n) : e(n, -1) {}
    bool sameSet(ll a, ll b) { return find(a) == find(b); }
    ll size(ll x) { return -e[find(x)]; }
    ll find(ll x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(ll a, ll b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
};

const ll maxcoord = ll(3e5) + 10;

signed main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n, m, k;
    cin >> n >> m >> k;

    vvi x(maxcoord);
    vvi y(maxcoord);

    rep(i, m)
    {
        ll a, b;
        cin >> a >> b;
        x[a].push_back(i);
        y[b].push_back(i);
    }

    UF uf(m);
    auto join = [&](vvi& axis)
    {
        rep(i, maxcoord)
        {
            repp(j, 1, sz(axis[i]))
            {
                uf.join(axis[i][0], axis[i][j]);
            }
        }
    };
    join(x);
    join(y);

    vi compsizes;
    vi vis(m);
    rep(i, m)
    {
        ll u = uf.find(i);
        if (vis[u]) continue;
        vis[u] = 1;
        compsizes.push_back(uf.size(u));
    }
    sort(all(compsizes));
    reverse(all(compsizes));
    ll ans = 0;
    rep(i, min(k, sz(compsizes)))
    {
        ans += compsizes[i];
    }
    cout << ans;

    return 0;
}
