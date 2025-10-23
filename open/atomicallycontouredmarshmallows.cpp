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

struct UF
{
    vi par, size;
    UF(int n) : par(n), size(n,1)
    {
        rep(i, n) par[i] = i;
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b])swap(a, b);
        par[b] = a;
        size[a] += size[b];
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    while (cin >> n >> m)
    {
        vector<tuple<int, int, int>> edges;
        rep(i, m)
        {
            int a, b, c;
            cin >> a >> b >> c;
            edges.emplace_back(c, a, b);
        }
        sort(all(edges));
        UF uf(n);
        int ans = 0;
        int ncomps = n;
        for (auto [w, a, b] : edges)
        {
            if (uf.find(a)!=uf.find(b))
            {
                uf.merge(a, b);
                ncomps--;
                ans += w;
            }
        }

        if (ncomps > 1) ans = -1;
        cout << ans << '\n';
    }


    return 0;
}
