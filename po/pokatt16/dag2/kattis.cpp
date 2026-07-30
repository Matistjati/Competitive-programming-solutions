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

using pd3 = tuple<double,double,ll>;
using pd = pair<double,double>;

#define slope(a,b) (((double)y[a]-y[b])/(x[a]-x[b]))

ll cross(pd o, pd a, pd b) { return (a.first - o.first)* (b.second - o.second) - (a.second - o.second) * (b.first - o.first); }

int kattis(int n, int h, int x[], int y[], int z[])
{
    vector<pd3> intervals;

    vector<pd> hull;

    // Solve all left points
    rep(i, n)
    {
        while (hull.size() > 1 && cross(hull[hull.size() - 2], hull[hull.size() - 1], make_pair(x[i], y[i])) >= 0) hull.pop_back();
        hull.push_back(make_pair(x[i], y[i]));
        if (z[i])
        {
            pair<double, double> bounds = { 0,x[n - 1] };
            if (sz(hull) > 1 && hull[hull.size() - 2].second > hull.back().second)
            {
                double slope = (hull.back().second - hull[hull.size() - 2].second) / (hull.back().first - hull[hull.size() - 2].first);
                double m = y[i] - slope * x[i];
                double isect = (h - m) / slope;
                bounds.first = max(bounds.first, isect);
            }

            intervals.emplace_back(bounds.first, bounds.second, i);
        }
    }

    hull = vector<pd>();

    // Solve all right points
    ll idx = sz(intervals)-1;
    for (int i = n-1; i >= 0; i--)
    {
        while (hull.size() > 1 && cross(hull[hull.size() - 2], hull[hull.size() - 1], make_pair(x[i], y[i])) <= 0) hull.pop_back();
        hull.push_back(make_pair(x[i], y[i]));
        if (z[i])
        {
            if (sz(hull) > 1 && hull[hull.size() - 2].second > hull.back().second)
            {
                double slope = (hull.back().second - hull[hull.size() - 2].second) / (hull.back().first - hull[hull.size() - 2].first);
                double m = y[i] - slope * x[i];
                double isect = (h - m) / slope;
                get<1>(intervals[idx]) = min(get<1>(intervals[idx]), isect);
            }
            idx--;
        }
    }

    vi left;

    sort(all(intervals), [](const pd3& lhs, const pd3& rhs)
        {
            return get<1>(lhs) < get<1>(rhs);
        });

    priority_queue<pd3> startpoints;

    ll ans = 0;

    vector<double> points;

    rep(i, intervals.size())
    {
        double l, r;
        ll j;
        tie(l, r, j) = intervals[i];
        if (z[j])
        {
            auto it = lower_bound(all(points), l);
            if (it==end(points)||*it>r)
            {
                ans++;
                points.push_back(r);
            }
        }
    }

    return ans;
}

#if LOCAL
int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n, h;
    cin >> n >> h;

    vi x(n);
    vi y(n);
    vi z(n);
    rep(i, n)
    {
        cin >> x[i];
        cin >> y[i];
        cin >> z[i];
    }

    cout << kattis(n, h, &x[0], &y[0], &z[0]);

    return 0;
}
#endif
