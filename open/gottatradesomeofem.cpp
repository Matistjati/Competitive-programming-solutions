#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

struct UF
{
    vi par, size;
    UF(int n) : par(n), size(n,1)
    {
        rep(i, n)par[i] = i;
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

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;
    UF uf(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        uf.merge(a, b);
    }

    map<int, vi> comps;
    rep(i, n) comps[uf.find(i)].push_back(i);
    for (auto& [_, comp] : comps)
    {
        if (sz(comp) < k)
        {
            cout << "impossible\n";
            return 0;
        }
    }

    vi ans(n);

    for (auto& [_, comp] : comps)
    {
        int c = 1;
        repe(u, comp)
        {
            ans[u] = c++;
            if (c > k) c = 1;
        }
    }

    repe(u, ans) cout << u << " ";

    return 0;
}
