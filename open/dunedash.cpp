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


int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    auto dist = [](p2 a, p2 b)
    {
        double dx = a.first-b.first;
        double dy = a.second - b.second;
        return hypot(dx, dy);
    };

    vector<p2> pts(n);
    repe(v, pts) cin >> v.first >> v.second;
    pair<double, p2> best = { 0,pts[0] };
    repe(v, pts)
    {
        best = max(best, make_pair(dist(pts[0],v),v));
    }
    sort(all(pts), [&](p2 a, p2 b)
        {
            return dist(a, best.second) < dist(b, best.second);
        });
    double ans = 0;
    rep(i, n - 1) ans += dist(pts[i], pts[i + 1]);
    cout << fixed << setprecision(15) << ans << '\n';

    return 0;
}
