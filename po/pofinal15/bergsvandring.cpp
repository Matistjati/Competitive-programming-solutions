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

double dist(p2 a, p2 b) {
    return hypot(a.first - b.first, a.second - b.second);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    double d;
    cin >> d;

    vector<p2> heights(n);
    rep(i, n) {
        int x, y;
        cin >> x >> y;
        heights[i] = { x,y };
    }
    
    vector<double> smallestDist(n, inf);
    smallestDist[0] = 0;
    rep(i, n) {
        double minSlope = -inf;
        repp(j, i + 1, n) {
            double slope = (heights[j].second - heights[i].second) / (double)(abs(heights[j].first - heights[i].first));
            
            if (slope < minSlope) continue;
            if (slope > minSlope) minSlope = slope;

            if (abs(slope) > d) continue;
            
            smallestDist[j] = min(smallestDist[j], smallestDist[i] + (j==i+1 ? 0 : dist(heights[j], heights[i])));
        }
    }

    if (smallestDist.back() == inf) smallestDist.back() = -1;

    cout << fixed << setprecision(15) << smallestDist[n - 1];

    return 0;
}
