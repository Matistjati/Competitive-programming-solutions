#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif
typedef pair<long double, long double> pd;
struct pointpair
{
    long double dist;
    pd a;
    pd b;
    pointpair(pd a, pd b, long double dist) : dist(dist), a(a), b(b) {}
};

inline long double dist(pd a, pd b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

inline pointpair closestbruteforce(vector<pd>& points)
{
    long double closest = inf;
    int besti = -1;
    int bestj = -1;
    rep(i, points.size())
        repp(j, i + 1, points.size())
        if (dist(points[i], points[j]) < closest)
        {
            closest = dist(points[i], points[j]);
            besti = i;
            bestj = j;
        }

    return pointpair(points[besti], points[bestj], closest);
}

inline pointpair stripbruteforce(vector<pd>& points, long double mindist)
{
    long double closest = inf;
    int besti = -1;
    int bestj = -1;
    rep(i, points.size())
    {
        int its = 0;
        for (int j = i + 1; j < points.size() && abs(points[i].second - points[j].second) < mindist; j++)
        {
            if (dist(points[i], points[j]) < closest)
            {
                closest = dist(points[i], points[j]);
                besti = i;
                bestj = j;
            }
            its++;
            if (its > 10)
            {
                break;
            }
        }
    }

    if (closest == inf) return pointpair(make_pair(0, 0), make_pair(0, 0), inf);
    return pointpair(points[besti], points[bestj], closest);
}

pointpair merge(pointpair a, pointpair b)
{
    if (a.dist < b.dist) return a;
    return b;
}

pointpair closestpair(vector<pd> sortx, vector<pd> sorty)
{
    if (sortx.size() <= 3)
    {
        return closestbruteforce(sortx);
    }

    int mid = sortx.size() / 2;
    vector<pd> leftcutx = vector<pd>(begin(sortx), begin(sortx) + mid);
    vector<pd> rightcutx = vector<pd>(begin(sortx) + mid + 1, end(sortx));

    vector<pd> leftcuty;
    vector<pd> rightcuty;
    rep(i, sorty.size())
    {
        if (sorty[i].first < leftcutx.back().first) leftcuty.push_back(sorty[i]);
        else rightcuty.push_back(sorty[i]);
    }

    pointpair leftclosest = closestpair(leftcutx, leftcuty);
    pointpair rightclosest = closestpair(rightcutx, rightcuty);

    long double closest = min(leftclosest.dist, rightclosest.dist);

    vector<pd> strip;
    rep(i, sorty.size())
    {
        if (abs(sorty[i].first - leftcutx.back().first) < closest)
        {
            strip.push_back(sorty[i]);
        }
    }

    return merge(merge(leftclosest, rightclosest), stripbruteforce(strip, closest));
}


long double circleOverlapArea(long double x1, long double y1, long double r1, long double x2, long double y2, long double r2) {
    long double d = std::hypot(x2 - x1, y2 - y1); // Distance between the centers

    // No overlap
    if (d >= r1 + r2) return 0.0;

    // One circle is completely within the other
    if (d <= std::abs(r1 - r2)) {
        long double r_min = std::min(r1, r2);
        return 3.14159265358979 * r_min * r_min;
    }

    // Calculate the areas of the segments
    long double angle1 = 2 * std::acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
    long double angle2 = 2 * std::acos((d * d + r2 * r2 - r1 * r1) / (2 * d * r2));

    long double area1 = 0.5 * r1 * r1 * (angle1 - std::sin(angle1));
    long double area2 = 0.5 * r2 * r2 * (angle2 - std::sin(angle2));

    // Overlapping area is the sum of the two segments
    return area1 + area2;
}


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
    long double dist() const { return sqrt((long double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    long double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(long double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
typedef long long T;
typedef Point<T> P;
const T INF = numeric_limits<T>::max();

bool on_x(const P& a, const P& b) { return a.x < b.x; }
bool on_y(const P& a, const P& b) { return a.y < b.y; }

struct Node {
    P pt; // if this is a leaf, the single point in it
    T x0 = INF, x1 = -INF, y0 = INF, y1 = -INF; // bounds
    Node* first = 0, * second = 0;

    T distance(const P& p) { // min squared distance to a point
        T x = (p.x < x0 ? x0 : p.x > x1 ? x1 : p.x);
        T y = (p.y < y0 ? y0 : p.y > y1 ? y1 : p.y);
        return (P(x, y) - p).dist2();
    }

    Node(vector<P>&& vp) : pt(vp[0]) {
        for (P p : vp) {
            x0 = min(x0, p.x); x1 = max(x1, p.x);
            y0 = min(y0, p.y); y1 = max(y1, p.y);
        }
        if (vp.size() > 1) {
            // split on x if width >= height (not ideal...)
            sort(all(vp), x1 - x0 >= y1 - y0 ? on_x : on_y);
            // divide by taking half the array for each child (not
            // best performance with many duplicates in the middle)
            int half = sz(vp) / 2;
            first = new Node({ vp.begin(), vp.begin() + half });
            second = new Node({ vp.begin() + half, vp.end() });
        }
    }
};

struct KDTree {
    Node* root;
    KDTree(const vector<P>& vp) : root(new Node({ all(vp) })) {}

    pair<T, P> search(Node* node, const P& p) {
        if (!node->first) {
            // uncomment if we should not find the point itself:
            // if (p == node->pt) return {INF, P()};
            return make_pair((p - node->pt).dist2(), node->pt);
        }

        Node* f = node->first, * s = node->second;
        T bfirst = f->distance(p), bsec = s->distance(p);
        if (bfirst > bsec) swap(bsec, bfirst), swap(f, s);

        // search closest side first, other side if needed
        auto best = search(f, p);
        if (bsec < best.first)
            best = min(best, search(s, p));
        return best;
    }

    // find nearest point to a point, and its squared distance
    // (requires an arbitrary operator< for Point)
    pair<T, P> nearest(const P& p) {
        return search(root, p);
    }
};

typedef tuple<long double, long double, long double> cat;
signed main()
{
    fast();

    int n;
    cin >> n;
    vector < cat> cats;
    long double rf, rm;
    cin >> rf >> rm;
    vector<cat> male;
    vector<cat> female;
    rep(i, n)
    {
        char type;
        long double x, y;
        cin >> type >> x >> y;
        long double r = rf;
        if (type == 'M') r = rm;
        cats.emplace_back(x, y, r);
        if (type == 'M') male.emplace_back(x, y, rm);
        if (type == 'F') female.emplace_back(x, y, rf);
    }

    long double ans = 0;
    if (n <= 2000)
    {
        rep(i, n)
        {
            long double x, y, r;
            tie(x, y, r) = cats[i];
            repp(j, i + 1, n)
            {
                long double x2, y2, r2;
                tie(x2, y2, r2) = cats[j];
                ans = max(ans, circleOverlapArea(x, y, r, x2, y2, r2));
            }
        }
        cout << fixed << setprecision(10) << ans;
    }
    else
    {
        auto trygender = [&](vector<cat> gender, long double r)
        {
            vector<pd> points;
            repe(c, gender) points.emplace_back(get<0>(c), get<1>(c));
            vector<pd> pointsysort(points);
            sort(all(points), [](const pd& a, const pd& b)
                {
                    if (a.first < b.first) return true;
            return false;
                });
            sort(all(pointsysort), [](const pd& a, const pd& b)
                {
                    if (a.second < b.second) return true;
            return false;
                });

            pointpair ans = closestpair(points, pointsysort);
            return circleOverlapArea(ans.a.first, ans.a.second, r, ans.b.first, ans.b.second, r);
        };

        auto trysecond = [&](vector<cat> haystack, vector<cat> needle)
        {
            long double best = 0;
            vector<P> catstack;
            repe(c, haystack) catstack.emplace_back(P(get<0>(c), get<1>(c)));
            KDTree kd(catstack);
            repe(c, needle)
            {
                P p = P(get<0>(c), get<1>(c));
                P closest = kd.nearest(p).second;
                best = max(best, circleOverlapArea(p.x, p.y, get<2>(c), closest.x, closest.y, get<2>(haystack[0])));
            }

            return best;
        };

        long double ans = trygender(male, rm);
        ans = max(ans, trygender(female, rf));
        ans = max(ans, trysecond(female, male));
        ans = max(ans, trysecond(male, female));
        cout << fixed << setprecision(10) << ans;

    }

    return 0;
}
