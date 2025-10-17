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

using pd = Point<double>;

const double epsilon = 1e-7;
const double twopi = 3.1415926535897932384*2;
vector<pd> ans;

vi child_cnt;
void dfs(int u, int p, vvi& adj)
{
    child_cnt[u] = 1;
    repe(e, adj[u]) if (e != p) dfs(e, u, adj), child_cnt[u] += child_cnt[e];
}


void place(int u, int p, pd my_pos, double sector_start, double sector_end, vvi& adj)
{
    double curr_angle = (sector_start + sector_end) / 2;
    double start = sector_start;
    repe(e, adj[u])
    {
        if (e == p) continue;
        double slice_width = (sector_end-sector_start-1e-4) * double(child_cnt[e])/child_cnt[u];
        double new_angle = start + slice_width / 2;
        pd newdir = pd(cos(new_angle), sin(new_angle));
        double next_part = start + slice_width;
        pd newpos = newdir+my_pos;

        ans[e] = newpos;
        place(e, u, newpos, start, start + slice_width, adj);
        start += slice_width;
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    ans.resize(n);
    vvi adj(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    child_cnt.resize(n);
    dfs(0, 0, adj);

    ans[0] = pd(0,0);
    place(0, 0, pd(0,0), 0, twopi-epsilon, adj);

    cout << fixed << setprecision(15);
    rep(i, n)
    {
        cout << ans[i].x << " " << ans[i].y << '\n';
    }

    return 0;
}
