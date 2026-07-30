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

vvi edges;
vector<p2> ab;

vvi dp;
vector<vector<map<ll, ll>>> antidp;
vector<vector<set<ll>>> edgesrem;
ll sumdist(ll u, ll p, ll d, ll depth)
{
    if (depth == 0)
    {
        return ab[u].first / (ab[u].second + d * d);
    }

    ll O = d * 8 + depth;
    ll ret = dp[u][d * 8 + depth];
    if (antidp[u][d * 8 + depth].count(p)) ret -= antidp[u][d * 8 + depth][p];
    for (auto it = edgesrem[u][O].begin(); it != edgesrem[u][O].end();)
    {
        if (*it == p)
        {
            it = next(it);
            continue;
        }

        ll k = sumdist(*it, u, d, depth - 1);
        ret += k;
        antidp[u][d * 8 + depth][*it] = k;
        dp[u][d * 8 + depth] += k;
        it = edgesrem[u][O].erase(it);
    }

    return ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;

    ab.resize(n);
    rep(i, n)
    {
        ll a, b;
        cin >> a >> b;
        ab[i] = { a,b };
    }

    edges.resize(n);
    edgesrem.resize(n, vector<set<ll>>(64));
    rep(i, n - 1)
    {
        ll a, b;
        cin >> a >> b;

        edges[a].push_back(b);
        edges[b].push_back(a);
        rep(j, 64)
        {
            edgesrem[a][j].insert(b);
            edgesrem[b][j].insert(a);
        }

    }
    dp.resize(n, vi(64, 0));
    antidp.resize(n, vector<map<ll, ll>>(64));

    ll bestnode = -1;
    ll bestdist = -1;
    rep(i, n)
    {
        ll v = 0;
        rep(d, 8)
        {
            v += sumdist(i, -1, d, d);
        }
        if (v > bestdist)
        {
            bestnode = i;
            bestdist = v;
        }
    }
    cout << bestnode;

    return 0;
}
