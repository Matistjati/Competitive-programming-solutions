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
    vector<int> par, size;
    
    UF(int n) : par(n), size(n, 1)
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
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    
    using ld = long double;
    using pd = pair<ld,ld>;
    while (t--) {
        int n;
        cin >> n;

        vector<pd> points;
        rep(i, n) {
            long double a,b;
            cin >> a >> b;
            points.emplace_back(a, b);
        }
        auto dist = [](pd a, pd b) {
            ld dx = a.first - b.first, dy = a.second - b.second;
            return sqrtl(dx * dx + dy * dy);
        };

        UF uf(n);
        vector<tuple<ld,int,int>> edges;
        rep(i, n)
        {
            repp(j, i + 1, n)
            {
                edges.emplace_back(dist(points[i], points[j]), i, j);
            }
        }
        sort(all(edges));

        ld ans = 0;
        repe(e, edges) {
            ld d;
            int i, j;
            tie(d, i, j) = e;
            if (uf.find(i)!=uf.find(j))
            {
                uf.merge(i, j);
                ans += d;
            }
        }
        cout << fixed << setprecision(2) << ans << '\n';
    }

    return 0;
}
