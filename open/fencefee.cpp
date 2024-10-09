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

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	repp(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
	return a;
}

signed main()
{
    fast();

    int f;
    cin >> f;
    map<p2, int> inds;
    vector<Point<int>> vertices;

	vector<p2> edges;
    vvi adj;
    rep(i, f)
    {
        int a1, b1, a2, b2;
        cin >> a1 >> b1 >> a2 >> b2;
        p2 pa = p2(a1, b1);
        p2 pb = p2(a2, b2);
        if (!inds.count(pa)) inds[pa] = sz(inds), adj.push_back({}), vertices.emplace_back(a1,b1);
        if (!inds.count(pb)) inds[pb] = sz(inds), adj.push_back({}), vertices.emplace_back(a2,b2);
        int i1 = inds[pa];
        int i2 = inds[pb];
        adj[i2].push_back(i1);
        adj[i1].push_back(i2);
		edges.emplace_back(i1, i2);
		edges.emplace_back(i2, i1);
    }

    rep(i, sz(adj))
    {
		sort(all(adj[i]), [&](int a, int b)
		{
			return (vertices[i] - vertices[a]).angle() < (vertices[i] - vertices[b]).angle();
		});
    }

	int topright = 0;
	rep(i, sz(vertices))
	{
		if (vertices[i].x > vertices[topright].x)
		{
			topright = i;
		}
		if (vertices[i].x==vertices[topright].x&&vertices[i].y>vertices[topright].y)
		{
			topright = i;
		}
	}

	int prev = topright;
	int u = adj[prev][0];
	int start = u;
	set<p2> forbid;
	do
	{
		forbid.insert(p2(prev, u));
		double angle = (vertices[u] - vertices[prev]).angle();
		int lo = -1;
		int hi = sz(adj[u]);

		while (lo + 1 < hi)
		{
			int mid = (lo + hi) / 2;
			double a = (vertices[u] - vertices[adj[u][mid]]).angle();
			if (angle >= (vertices[u] - vertices[adj[u][mid]]).angle())
			{
				lo = mid;
			}
			else hi = mid;
		}
		prev = u;
		if (hi == sz(adj[u])) u = adj[u][0];
		else u = adj[u][hi];

	} while (u != start);


	map<vi, vi> cycles;

	repe(e,edges)
	{
		if (forbid.find(e)!=forbid.end())
		{
			continue;
		}
		vi cycle;
		int prev = e.first;
		int u = e.second;
		p2 start = p2(prev,u);
		bool good = 1;
		do
		{
			cycle.push_back(u);
			double angle = (vertices[u] - vertices[prev]).angle();
			int lo = -1;
			int hi = sz(adj[u]);

			while (lo+1<hi)
			{
				int mid = (lo + hi) / 2;
				double a = (vertices[u] - vertices[adj[u][mid]]).angle();
				if (angle >= (vertices[u] - vertices[adj[u][mid]]).angle())
				{
					lo = mid;
				}
				else hi = mid;
			}
			prev = u;
			if (hi == sz(adj[u])) u = adj[u][0];
			else u = adj[u][hi];

		} while (p2(prev,u) != start);
		if (!good) continue;

		vi c(cycle);
		sort(all(c));
		cycles[c] = cycle;
	}
	double ans = 0;
	repe(c, cycles)
	{
		vector<Point<double>> points;
		repe(u, c.second) points.push_back(Point<double>(vertices[u].x, vertices[u].y));
		double k = polygonArea2(points) / 2;
		ans += k * k;
	}
	cout << fixed << setprecision(15) << ans;

    return 0;
}
