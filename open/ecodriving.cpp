#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

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

signed main()
{
    fast();

    int n, m, d;
    cin >> n >> m >> d;
    vector<Point<int>> points(n);
    rep(i, n)
    {
        cin >> points[i].x >> points[i].y;
    }
    vvi adj(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    double lo = 0;
    double hi = 6.28318530718+1;
    rep(i, 100)
    {
        double mid = (lo + hi) / 2;
        // all turns less than mid
        bool good = 0;
        priority_queue<tuple<double,int,int>> pq;
        pq.emplace(0, 0, 0);
        double dist = inf;
        vvi vis(n, vi(n));
        while (sz(pq))
        {
            double dis;
            int u, p;
            tie(dis, u, p) = pq.top();
            pq.pop();

            if (vis[u][p]) continue;
            vis[u][p] = 1;

            if (u==n-1)
            {
                dist = -dis;
                break;
            }

            repe(e, adj[u])
            {
                if (u == 0 && p == 0) pq.emplace(dis - (points[u]- points[e]).dist(), e, u);
                else
                {
                    Point<int> into = (points[u] - points[p]);
                    Point<int> leaving = (points[e] - points[u]);
                    double theta = acos(into.dot(leaving) / (into.dist() * leaving.dist()));
                    if (theta <=mid)
                    {
                        pq.emplace(dis - (points[u] - points[e]).dist(), e, u);
                    }
                }
            }
        }

        if (dist <= d)
        {
            hi = mid;
        }
        else lo = mid;
    }
    if (lo>6.28318531)
    {
        cout << "Impossible";
    }
    else cout << fixed << setprecision(15) << lo/6.28318530718*360;

    return 0;
}
