#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
ll inf = ll(1e18);
#define rep(i,lo,hi) for (ll i=lo; i<hi;i++)
#define pb push_back

vi daprimes;
vi vis;
vi dep;
vi colors;

ll countsize(ll u, ll p, vector<vi>& edges)
{
    ll ret = 0;
    if (colors[u] == -1) ret = 1;

    for (auto& e : edges[u]) if (e != p) ret += countsize(e, u, edges);
    return ret;
}

void dfs(ll u, ll p, ll c, vector<vi>& edges)
{
    if (u != 0 && colors[u] == -1)colors[u] = c * colors[p];

    vector<tuple<ll, ll, ll>> edg;

    for (auto& e : edges[u])
    {
        if (e != p) edg.emplace_back(-dep[e], -countsize(e, u, edges), e); //dfs(e,u,colors,edges);
    }
    sort(edg.begin(), edg.end());

    for (auto& e : edg)
    {
        int v = get<2>(e);
        if (countsize(v, u, edges))
        {
            dfs(v, u, c, edges);
            break;

        }
    }
}

void dfs2(ll u, ll p, ll d, vi& dep, vector<vi>& edges)
{
    dep[u] = d;

    for (auto& e : edges[u]) if (e != p) dfs2(e, u, d + 1, dep, edges);
}

const ll MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;
vi eratosthenesSieve(ll lim = MAX_PR - 1) {
    isprime.set(); isprime[0] = isprime[1] = 0;
    for (ll i = 4; i < lim; i += 2) isprime[i] = 0;
    for (ll i = 3; i * i < lim; i += 2) if (isprime[i])
        for (ll j = i * i; j < lim; j += i * 2) isprime[j] = 0;
    vi pr;
    rep(i, 2, lim) if (isprime[i]) pr.push_back(i);
    return pr;
}

int main()
{
    daprimes = eratosthenesSieve();

    ll n;
    cin >> n;
    vector<vi> edges(n);
    rep(i, 0, n - 1)
    {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    vis.resize(n);
    dep.resize(n);
    dfs2(0, 0, 0, dep, edges);
    colors.resize(n, -1);
    colors[0] = 1;

    ll cnt = 0;
    while (countsize(0, 0, edges))
    {
        dfs(0, 0, daprimes[cnt], edges);
        cnt++;
    }

    rep(i, 0, n)
    {
        if (colors[i] > ll(1e18) || colors[i] < 0)
        {
            assert(0);
        }
    }
    rep(i, 0, n) cout << colors[i] << " ";

    return 0;
}