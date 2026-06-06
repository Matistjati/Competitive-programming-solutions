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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

using P = Point<ll>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,q;
    cin >> n >> q;

    vector<pair<P,int>> pts(n);
    rep(i,n) cin >> pts[i].first.x >> pts[i].first.y, pts[i].second = i;
    sort(all(pts), [](pair<P,int> a, pair<P,int> b) {
        return a.first.angle() < b.first.angle();
    });

    while (q--) {
        P p;
        cin >> p.x >> p.y;
        if (p==P(0,0)) {
            cout << "1\n";
            continue;
        }

        int cand=0;
        auto test = [&](int i) {
            if (i >= 0 && i < n && make_pair((p-pts[i].first).dist2(),pts[i].second) < make_pair((p-pts[cand].first).dist2(),pts[cand].second)) {
                cand=i;
            }
        };
        test(n-1);

        auto it = lower_bound(all(pts), make_pair(p,-1), [](pair<P,int> a, pair<P,int> b) {
            return a.first.angle() < b.first.angle();
        });
        test(it-begin(pts));
        test(it-begin(pts)-1);
        test(it-begin(pts)+1);
        cout << pts[cand].second+1 << '\n';
    }

    return 0;
}
