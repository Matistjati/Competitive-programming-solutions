#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};


using P = Point<ll>;
bool on_line(P a, P b, P c)
{
    return (a - b).cross(a - c) == 0;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<P> pts(n);
    repe(p, pts) cin >> p.x >> p.y;

    uniform_int_distribution<int> dist(0, n - 1);
    mt19937 rng(42);

    vector<char> killed(n);
    auto win = []()
    {
        cout << "possible\n";
        exit(0);
    };
    vector<short> alive;
    vector<short> alive2;
    rep(it, 8)
    {
        int ia = dist(rng);
        int ib = dist(rng);
        if (ia == ib) continue;
        P a = pts[ia];
        P b = pts[ib];
        alive.clear();
        rep(i, n) if (!on_line(a, b, pts[i])) alive.push_back(i);

        rep(it2, 7)
        {
            if (sz(alive) <= 2) win();
            uniform_int_distribution<int> dist2(0, sz(alive) - 1);
            int ja = dist2(rng);
            int jb = dist2(rng);
            if (ja == jb) continue;
            P c = pts[alive[ja]];
            P d = pts[alive[jb]];
            alive2.clear();
            repe(a, alive) if (!on_line(c, d, pts[a])) alive2.push_back(a);

            if (sz(alive2) <= 2) win();
            P e = pts[alive2[0]];
            P f = pts[alive2[1]];
            int numon = 0;
            repe(i, alive2) numon += on_line(e, f, pts[i]);

            if (numon == sz(alive2)) win();
        }
    }
    cout << "impossible\n";

    return 0;
}
