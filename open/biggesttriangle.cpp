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

using P = Point<double>;

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
        auto d = (e1 - s1).cross(e2 - s2);
        if (d == 0) // if parallel
                return {-(s1.cross(e1, s2) == 0), P(0, 0)};
        auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
        return {1, (s1 * p + e1 * q) / d};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    vector<pair<P,P>> pts(n);
    rep(i,n) cin >> pts[i].first.x >> pts[i].first.y >> pts[i].second.x >> pts[i].second.y;

    double ans = 0;
    rep(i,n) {
        repp(j,i+1,n) {
            repp(k,j+1,n) {
                vector<pair<P,P>> lines = {pts[i],pts[j],pts[k]};
                bool ok = 1;
                rep(a, 3) {
                    repp(b,a+1,3) {
                        ok &= lineInter<P>(lines[a].first, lines[a].second, lines[b].first, lines[b].second).first == 1;
                    }
                }
                if (!ok) continue;
                P P1 = lineInter<P>(lines[0].first, lines[0].second, lines[1].first, lines[1].second).second;
                P P2 = lineInter<P>(lines[0].first, lines[0].second, lines[2].first, lines[2].second).second;
                P P3 = lineInter<P>(lines[1].first, lines[1].second, lines[2].first, lines[2].second).second;
                double dist = (P1-P2).dist() + (P3-P1).dist() + (P3-P2).dist();

                ans = max(ans,dist);
            }
        }
    }
    if (ans==0) {
        cout << "no triangle\n";
    }
    else {
        cout << fixed << setprecision(15) << ans << '\n';
    }

    return 0;
}
