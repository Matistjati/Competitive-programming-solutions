#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
//const int inf = int(1e18);

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


struct Line {
	mutable double k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(double x) const { return p < x; }
};

static const double inf = numeric_limits<double>::infinity();
struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	double div(double a, double b) { // floored division
		return a / b;
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(double k, double m) {
		auto z = insert({ k, m, 0. }), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	double query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

signed main()
{
	fast();

	int live, n, c;
	cin >> live >> n >> c;
	vector<double> dp(n + 2, -1e18);
	dp[0] = live;
	vector<double> pills(n + 2);
	vi time(n + 2);
	time[0] = 0;
	time.back() = 1e18;
	pills[0] = 1;

	vector<pair<int, double>> pillsin;
	rep(i, n)
	{
		int s;
		int x, y;
		cin >> s >> y >> x;
		pillsin.emplace_back(s, y/ (x+0.));
	}
	sort(all(pillsin));
	rep(i, n)
	{
		pills[i+1] = pillsin[i].second;
		time[i + 1] = pillsin[i].first;
	}

	double ans = 0;
	LineContainer dplines;
	auto insert = [&](int i)
	{
		dplines.add(-1.0 / pills[i], dp[i] - c + time[i] / pills[i]);

	};
	insert(0);
	repp(i, 1, n + 2)
	{
		dp[i] = max(dp[i], dplines.query(time[i]));
		if (dp[i]>0) ans = max(ans, time[i]+dp[i]*pills[i]);
		insert(i);
	}
	cout << fixed << setprecision(15) << ans;

	return 0;
}
