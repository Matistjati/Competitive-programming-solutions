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

p2 deepest(ll u, ll p, ll d, vvi& edges, vi& isfruit)
{
    if (isfruit[u]) return { d,u };

    p2 ret = { 0,-1 };
    repe(e, edges[u]) if (e != p) ret = max(ret, deepest(e, u, d + 1, edges, isfruit));
    return ret;
}

ll up[500000 + 10][20];
void finddepth(ll u, ll p, ll d, vvi& edges, vi& isfruit, vector<p2>& depth)
{
    up[u][0] = p;

    repp(d, 1, 20)
    {
        up[u][d] = up[up[u][d - 1]][d - 1];
    }

    if (isfruit[u]) depth.emplace_back(d, u);
    repe(e, edges[u]) if (e != p) finddepth(e, u, d + 1, edges, isfruit, depth);
}

void dfsdown(ll u, ll p, vi& vis, vvi& edges, vi& dist)
{
    if (vis[u]) return;
    vis[u] = 1;
    repe(e, edges[u])
    {
        if (e != p && dist[u] == dist[e] + 1)
        {
            dfsdown(e, u, vis, edges, dist);
        }
    }
}

string solvesmart(vector<p2>& edgelist, vi& fruits)
{
    ll n = edgelist.size() + 1;
    ll f = fruits.size();

    if (f == 0)
    {
        return "0";
    }

    vvi edges(n);
    rep(i, n - 1)
    {
        ll a = edgelist[i].first - 1;
        ll b = edgelist[i].second - 1;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    queue<tuple<int,int,int,int>> q;
    vvi colors(n);

    vi isfruit(n);
    vi size(n);

    rep(i, f)
    {
        ll p = --fruits[i];
        isfruit[p] = 1;
        colors[p] = { p };
        q.emplace(p, 0, p, 0);
        size[p] = 1;
    }
    vi time(n, inf);

    vi vis(n);

    vi parent(n);
    rep(i, n) parent[i] = i;

    vvi endpoints(n);
    vi times(n);
    vi nodedepth(n);

    while (q.size())
    {
        ll u, t, p, d;
        tie(u, t, p, d) = q.front();
        q.pop();

        if (time[u] < t) // too late- parent is endpoint
        {
            continue;
        }
        time[u] = t;

        if (u != p)size[u] += size[p];
        times[p]++;
        nodedepth[u] = d;

        if (vis[u]) continue;
        vis[u] = 1;

        repe(e, edges[u]) if (e != p) q.emplace(e, t + 1, u, d + 1);
    }

    ll root = deepest(fruits[0], fruits[0], 0, edges, isfruit).second;

    vector<p2> depth;
    finddepth(root, root, 0, edges, isfruit, depth);
    sort(all(depth));
    reverse(all(depth));

    vi ans;
    vi istaken(n);
    ll taken = 0;

    vi finalvis(n);
    rep(i, depth.size())
    {
        ll target = depth[i].second;
        if (istaken[target])
        {
            continue;
        }

        ll node = target;
        for (ll d = 19; d >= 0; d--)
        {
            ll g = up[node][d];
            if (nodedepth[g] == nodedepth[node] + (1 << d))
            {
                node = g;
            }
        }

        ans.push_back(node);

        dfsdown(node, node, istaken, edges, nodedepth);

    }

    stringstream ret;
    ret << ans.size() << "\n";
#if !_LOCAL
    repe(p, ans)
    {
        ret << p + 1 << " ";
    }
#endif
    return ret.str();
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n, f;
    cin >> n >> f;
    vector<p2> edgelist;
    rep(i, n - 1)
    {
        ll a, b;
        cin >> a >> b;
        edgelist.emplace_back(a, b);
    }
    vector<ll> fruits(f);
    for (auto& v : fruits) cin >> v;

    cout << solvesmart(edgelist, fruits) << '\n';

    return 0;
}
