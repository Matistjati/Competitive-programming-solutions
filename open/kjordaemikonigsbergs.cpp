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
    int ncomps;
    UF(int n) : par(n), size(n, 1), ncomps(n)
    {
        rep(i, n) par[i] = i;
    }
    int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
    void merge(int a, int b)
    {
        a = find(a); b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        par[b] = a;
        size[a] += size[b];
        ncomps--;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    auto die = []()
        {
            cout << "Omogulegt!";
            exit(0);
        };

    int n;
    cin >> n;
    vi deg(n);
    repe(v, deg) cin >> v;
    UF uf(n);

    vector<p2> smol(n);
    rep(i, n) smol[i] = p2(deg[i], i);
    sort(all(smol));
    priority_queue<p2> highest;
    vi lazyrem(n);
    vi del(n);
    rep(i, n) if (deg[i] > 0) highest.emplace(deg[i], i);
    vector<p2> edg;
    for (auto [deg, i] : smol)
    {
        del[i] = 1;
        deg -= lazyrem[i];
        int numgood = 0;
        vector<p2> pop;
        while (sz(pop) < deg)
        {
            while (sz(highest) && del[highest.top().second])
            {
                highest.pop();
            }
            if (highest.empty()) die();
            pop.push_back(highest.top());
            highest.pop();
        }

        for (auto& [d, u] : pop)
        {
            if (u != i)
            {
                lazyrem[u]++;
                d--;
                edg.emplace_back(i, u);
                uf.merge(i, u);
            }

            if (d > 0) highest.emplace(d, u);
        }
    }
    while (sz(highest) && del[highest.top().second])
    {
        highest.pop();
    }
    if (sz(highest)) die();
    if (uf.ncomps > 1) die();
    cout << n << " " << sz(edg) << '\n';
    repe(u, edg)
    {
        cout << u.first + 1 << " " << u.second + 1 << "\n";
    }

    return 0;
}
