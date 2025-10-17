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


struct Line {
    ll k, m;
    long double xRight; // y = kx + m, and intersection with next line
    int origin_node = -1;
    bool operator<(const Line& o) const {
        if (k != o.k) return k < o.k;
        return origin_node < o.origin_node;
    }
    bool operator<(ll x) const {
        return xRight < x;
    }
    Line operator+(const Line& other) const {
        return { k + other.k,m + other.m, 0, origin_node };
    }
    ll eval(ll x) const {
        return k * x + m;
    }
};

#if _LOCAL
#include <__msvc_int128.hpp>
using big_signed = _Signed128;
#else
using big_signed = __int128;
#endif

struct UpperHull {
    vector<Line> hull;
    static long double div(ll a, ll b) { // floored division
        return (long double)a / b;
    }
    bool intersection_geq(const Line& A, const Line& B, const Line& C) {
        auto left = (big_signed)(B.m - A.m) * (A.k - C.k);
        auto right = (big_signed)(C.m - A.m) * (A.k - B.k);
        return left > right;
    }
    void push_back(Line& l) {
        if (sz(hull)) assert(l.k >= hull.back().k);
        if (sz(hull) && hull.back().k == l.k) {
            if (hull.back().m >= l.m) return;
            hull.pop_back();
        }
        while (sz(hull) >= 2 && intersection_geq(hull[sz(hull) - 2], hull.back(), l)) {
            hull.pop_back();
        }
        hull.push_back(l);
    }
    UpperHull() {}
    UpperHull(vector<Line>& a) {
        sort(all(a));
        for (auto l : a) {
            push_back(l);
        }
        rep(i, sz(hull) - 1) hull[i].xRight = div(hull[i + 1].m - hull[i].m, hull[i].k - hull[i + 1].k);
        if (sz(hull)) hull.back().xRight = 1e18;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, ll>> edges;
    rep(i, m)
    {
        ll a, b, l;
        cin >> a >> b >> l;
        a--; b--;
        edges.emplace_back(a, b, l);
    }

    auto dists = [&](int start)
    {
        vvi dist(n, vi(n, inf));
        dist[0][start] = 0;

        rep(nodes, n - 1)
        {
            const vi& row = dist[nodes];
            for (auto [u, v, w] : edges)
            {
                dist[nodes + 1][v] = min(dist[nodes + 1][v], w + row[u]);
                dist[nodes + 1][u] = min(dist[nodes + 1][u], w + row[v]);
            }
        }

        rep(i, n) repp(j, i + 1, n) swap(dist[i][j], dist[j][i]);

        return dist;
    };

    vvi from_start = dists(0);
    vvi from_end = dists(n - 1);


    vi start_to_end = from_start[n - 1];
    vector<Line> to;
    rep(j, sz(start_to_end)) if (start_to_end[j] != inf) to.push_back({ -j,-start_to_end[j],0,(int)n - 1 });
    UpperHull h(to);
    // find all lines that are part of the lower hull for x>=0
    vector<Line> filter;
    repe(l, h.hull) if (l.xRight >= 0) filter.push_back(l);
    h = UpperHull(filter);

    vi any(n);
    for (auto l : h.hull)
    {
        ll k = -l.k;
        rep(u, n)
        {
            if (any[u]) continue;
            rep(j, k + 1)
            {
                if (from_start[u][j] + from_end[u][k - j] == from_start[n - 1][k])
                {
                    any[u] = 1;
                }
            }
        }
    }

    int ans = 0;
    rep(i, n)
    {
        if (!any[i]) ans++;
    }
    cout << ans << '\n';
    rep(i, n)
    {
        if (!any[i]) cout << i + 1 << " ";
    }

    return 0;
}
