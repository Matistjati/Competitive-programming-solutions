#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define repe(i, arr) for (auto& i : arr)
#define rep(i, b) for(ll i = 0; i < (b); ++i)
#define repp(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)x.size())

struct UF
{
    vi par, size;
    UF(int n) : par(n), size(n, 1)
    {
        iota(all(par), 0);
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
};

void solve(int u, int p, vvi& adj, vi& path)
{
    path.push_back(u);

    repe(c, adj[u])
    {
        if (c == p) continue;
        repe(c2, adj[c])
        {
            if (c2 == u) continue;
            solve(c2, c, adj, path);
        }
        path.push_back(c);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;
    UF uf(n);
    vvi adj(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (uf.find(a)!=uf.find(b))
        {
            uf.merge(a, b);
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }

    vi path;
    solve(0, 0, adj, path);
    repe(u, path)
    {
        cout << u + 1 << ' ';
    }

    return 0;
}
