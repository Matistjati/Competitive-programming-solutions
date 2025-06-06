#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

vi pardist;
vi par;
vi viruscnt;

int it = 10;
vi vis;
p2 find(int u)
{
    if (vis[u] == it) return p2(-1, -1);
    vis[u] = it;
    if (viruscnt[u] != 0) return p2(0, u);
    if (par[u] == par[0])
    {
        return p2(pardist[u], par[u]);
    }
    p2 res = find(par[u]);
    res.first += pardist[u];
    if (u != par[0])
    {
        pardist[u] = res.first;
        par[u] = res.second;
    }
    return res;
}

signed main()
{
    fast();

    int n;
    cin >> n;
    vis.resize(n);
    par.resize(n);
    pardist.resize(n, 1);
    repe(v, par) cin >> v, v--;
    viruscnt.resize(n);
    repe(v, viruscnt) cin >> v;
    priority_queue<p2> pq;
    rep(i, n) if (viruscnt[i] > 0) pq.emplace(viruscnt[i], -i);

    int numnegative = 0;
    repe(v, viruscnt) if (v < 0) numnegative++;

    int ans = 0;

    while (sz(pq) && numnegative)
    {
        auto [v, u] = pq.top();
        pq.pop();
        u = -u;

        if (viruscnt[u] != v) continue;


        it++;
        viruscnt[u] = 0;
        p2 p = find(u);
        if (p.second == -1 || p.second == u) break;
        if (p.second == 0 && par[par[0]] == 0 && viruscnt[p.second]==0) break;

        ans += p.first;
        if (viruscnt[p.second] < 0 && v + viruscnt[p.second] >= 0) numnegative--;
        viruscnt[p.second] += v;
        if (viruscnt[p.second] > 0) pq.emplace(viruscnt[p.second], -p.second);
    }

    if (numnegative == 0) cout << ans;
    else cout << "never";

    return 0;
}
