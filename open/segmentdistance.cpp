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

using ld = long double;

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
    ld dist() const { return sqrtl((ld)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    ld angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

using P = Point<ld>;
ld segDist(P& s, P& e, P& p) {
    if (s==e) return (p-s).dist();
    auto d = (e-s).dist2(), t = min(d,max((ld).0,(p-s).dot(e-s)));
    return ((p-s)*d-(e-s)*t).dist()/d;
}

template<typename T>
ld gss(ld a, ld b, T f) {
    ld r = (sqrtl(5)-1)/2, eps = 1e-9;
    ld x1 = b - r*(b-a), x2 = a + r*(b-a);
    ld f1 = f(x1), f2 = f(x2);
    while (b-a > eps)
        if (f1 < f2) { //change to > to find maximum
            b = x2; x2 = x1; f2 = f1;
            x1 = b - r*(b-a); f1 = f(x1);
        } else {
            a = x1; x1 = x2; f1 = f2;
            x2 = a + r*(b-a); f2 = f(x2);
        }
    return a;
}

using Segment = pair<P,P>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int tc;
    cin >> tc;
    while (tc--) {
        Segment a,b;
        cin >> a.first.x >> a.first.y >> a.second.x >> a.second.y;
        cin >> b.first.x >> b.first.y >> b.second.x >> b.second.y;
        auto d = [&](ld t) {
            P delta = b.second-b.first;
            P p = b.first + delta * t;
            return segDist(a.first, a.second, p);
        };

        ld t = gss(0,1,d);
        cout << fixed << setprecision(2) << d(t) << '\n';
    }

    return 0;
}
