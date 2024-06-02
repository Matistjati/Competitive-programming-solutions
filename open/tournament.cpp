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

#if _LOCAL
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

int sqr(int x)
{
	return x * x;
}

int memo[100][100][100];
int iglimit;
int best_(int i, int prev, int ignored, vector<pair<int, string>>& s)
{
	if (ignored > iglimit)
	{
		return inf;
	}
	if (i == sz(s))
	{
		return (prev == -1 && ignored == iglimit) ? 0 : inf;
	}
	int& v = memo[i][prev + 1][ignored];
	if (v != -1) return v;
	int ret = best_(i + 1, prev, ignored + 1, s);
	if (prev == -1)
	{
		ret = min(ret, best_(i + 1, i, ignored, s));
	}
	else
	{
		ret = min(ret, sqr(s[prev].first - s[i].first) + best_(i + 1, -1, ignored, s));
	}
	return v = ret;
}

struct pos
{
	int i, taken;
};
struct line // kx+m
{
	double k, m;
	int placements;
	pos from;
	double eval(int x) {
		return k * x + m;
	}
	double isect(line other) { return double(other.m - m) / (k - other.k); }
};

signed main()
{
	fast();

	//ifstream in("c:\\users\\matis\\desktop\\comp_prog\\x64\\debug\\in.txt");
	//cin.rdbuf(in.rdbuf());

	int n;
	while (cin >> n && n != 0)
	{
		vector<pair<double, string>> contestants;
		rep(i, n)
		{
			string name;
			int s;
			cin >> name >> s;
			contestants.emplace_back(s, name);
		}
		sort(contestants.rbegin(), contestants.rend());

		int p;
		rep(i, n)
		{
			if ((n - i) % 2 == 0)
			{
				int r = (n - i) / 2 + i;
				bool good = 1;
				while (r > 1) good &= r % 2 == 0, r /= 2;
				if (good)
				{
					p = i;
					break;
				}
			}
		}
		iglimit = p;

		vector<pair<double, string>> cc(contestants);
		reverse(all(cc));
		// make all number of knights reachable by adding small epsilon, breaking ties
		rep(i, sz(contestants)) cc[i].first += 0.00000000001 * i;
		reverse(all(cc));
		cc.insert(cc.begin(), { 0, "LIGMA" });
		cc.push_back({ 0, "LIGMA" });
		pos defaultpos = pos({ -1,-1 });
		

		
		line nullline = line({ 0,inf,0,defaultpos });
		auto add = [](deque<line>& cht, line l)
		{
			while (sz(cht) > 1 && cht.back().isect(l) < cht[sz(cht) - 2].isect(l))
			{
				cht.pop_back();
			}
			cht.push_back(l);
		};
		auto query = [nullline](deque<line>& cht, int x)
		{
			if (sz(cht) == 0) return nullline;
			while (sz(cht) > 1 && cht.back().eval(x) > cht[sz(cht) - 2].eval(x))
			{
				cht.pop_front();
			}
			return cht.back();
		};

		typedef pair<double, int> dpval;
		vector<pos> dpfreepos(n + 2, defaultpos);
		vector<pos> dptakenpos(n + 2, defaultpos);
		vector<dpval> dpfree(n + 2, dpval(inf, inf));

		// O(klog(?)) for each testcase, using alien dp + convex hull trick
		auto alien = [&](double lambda)
		{
			rep(i, n + 2) dpfree[i] = dpval(inf, inf);
			deque<line> dplines;
			dpval smol = dpval(0, 0);
			pos smolpos = pos(0, 1);
			repp(i, 1, n + 2)
			{
				line best = query(dplines, cc[i].first);
				double v = best.eval(cc[i].first);
				v += cc[i].first * cc[i].first;
				v -= lambda;
				dptakenpos[i] = best.from;

				dpfree[i] = smol;
				dpfreepos[i] = smolpos;
				line dpline(- 2 * cc[i].first, dpfree[i].first+ cc[i].first * cc[i].first, dpfree[i].second, pos({i, 0}));
				add(dplines, dpline);
				
				if (v < smol.first) smol = dpval(v, best.placements + 1), smolpos = pos(i, 1);
				
			}
			return dpfree.back();
		};
		double lo = -int(1e9);
		double hi = int(1e9);
		rep(i, 100)
		{
			double mid = (lo + hi) / 2;
			if (alien(mid).second >= (n - p)/2)
			{
				hi = mid;
			}
			else lo = mid;
		}
		dpval res = alien(hi);
		assert(res.second == (n - p)/2);
		// lowest total cost of remaining knights
		//cout << int(round(alien(hi).first + (n - p)/2 * hi)) << "\n";
		
		set<string> used;
		pos cp = dpfreepos.back();
		while (cp.i != -1)
		{
			used.insert(cc[cp.i].second);
			if (cp.taken) cp = dptakenpos[cp.i];
			else cp = dpfreepos[cp.i];
		}

		set<string> unused;
		repe(c, contestants) if (used.find(c.second) == used.end()) unused.insert(c.second);
		cout << sz(unused) << "\n";
		repe(c, unused) cout << c << "\n";
		
	}

	return 0;
}
