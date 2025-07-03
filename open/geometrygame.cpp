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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }


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

    vector<Point<int>> pts(4);
    repe(p, pts) cin >> p.x >> p.y;

	vi squared_dists;
	rep(i, 4)
	{
		squared_dists.push_back((pts[i] - pts[(i + 1)%4]).dist2());
	}
	bool all_same_angle = 1;

	rep(i, 4)
	{
		Point<int> ba = pts[i] - pts[((i - 1) + 4) % 4];
		Point<int> bc = pts[(i+1)%4] - pts[i];
		if (ba.dot(bc) != 0) all_same_angle = false;
	}
	
	bool all_same_dist = 1;
	rep(i, 4) all_same_dist &= squared_dists[i] == squared_dists[0];

	int parallel_count = 0;
	rep(i, 2)
	{
		Point<int> v1 = pts[i] - pts[(i + 1) % 4];
		Point<int> v2 = pts[(i + 2) % 4] - pts[(i + 3) % 4];
		if (v1.cross(v2) == 0) parallel_count++;
	}

	bool iskite = false;
	rep(i, 4)
	{
		if ((squared_dists[i]==squared_dists[(i+3)%4]&&squared_dists[(i+1)%4]==squared_dists[(i+2)%4])
			|| (squared_dists[i]==squared_dists[(i+1)%4]&&squared_dists[(i+2)%4]==squared_dists[(i+3)%4]))
		{
			iskite = 1;
		}
	}

	if (all_same_dist&&all_same_angle)
	{
		cout << "square";
		return 0;
	}
	else if (all_same_angle)
	{
		cout << "rectangle";
		return 0;
	}
	else if (all_same_dist)
	{
		cout << "rhombus";
		return 0;
	}
	else if (parallel_count==2)
	{
		cout << "parallelogram";
		return 0;
	}
	else if (parallel_count==1)
	{
		cout << "trapezium";
		return 0;
	}
	else if (iskite)
	{
		cout << "kite";
		return 0;
	}
	else
	{
		cout << "none";
		return 0;
	}

    return 0;
}
