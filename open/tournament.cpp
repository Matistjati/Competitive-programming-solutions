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

	ofstream out;
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

		vector<pair<double, string>> cc(contestants);
		reverse(all(cc));
		// make all number of knights reachable by adding small epsilon, breaking ties
		rep(i, sz(contestants)) cc[i].first += 0.00000000001 * i;
		reverse(all(cc));
		cc.insert(cc.begin(), { 0, "LIGMA" });
		cc.push_back({ 0, "LIGMA" });
		pos defaultpos = pos({ -1,-1 });



		line nullline = line({ 0,inf,0,defaultpos });
		int backind = 0;
		vector<line> dplines(n+2);
		auto add = [&backind](vector<line>& cht, line l)
		{
			while (backind > 0 && cht[backind].isect(l) < cht[backind - 1].isect(l))
			{
				backind--;
			}
			cht[++backind] = l;
		};
		auto query = [&backind, nullline](vector<line>& cht, int x)
		{
			if (backind == -1) return nullline;
			while (backind > 0 && cht[backind].eval(x) > cht[backind].eval(x))
			{
				backind--;
			}
			return cht[backind];
		};

		typedef pair<double, int> dpval;
		vector<pos> dpfreepos(n + 2, defaultpos);
		vector<pos> dptakenpos(n + 2, defaultpos);

		// O(klog(?)) for each testcase, using alien dp + convex hull trick
		auto alien = [&](double lambda)
		{
			backind = -1;
			dpval smol = dpval(0, 0);
			pos smolpos = pos(0, 1);
			repp(i, 1, n + 2)
			{
				line best = query(dplines, cc[i].first);
				double v = best.eval(cc[i].first);
				v += cc[i].first * cc[i].first;
				v -= lambda;
				dptakenpos[i] = best.from;

				dpfreepos[i] = smolpos;
				line dpline(-2 * cc[i].first, smol.first + cc[i].first * cc[i].first, smol.second, pos({ i, 0 }));
				add(dplines, dpline);

				if (i != n + 1 && v < smol.first) smol = dpval(v, best.placements + 1), smolpos = pos(i, 1);

			}
			return smol;
		};
		double lo = 0;
		double hi = int(1e8);
		rep(i, 58)
		{
			double mid = (lo + hi) / 2;
			if (alien(mid).second >= (n - p) / 2)
			{
				hi = mid;
			}
			else lo = mid;
		}
		dpval res = alien(hi);
		assert(res.second == (n - p) / 2);
		// lowest total cost of remaining knights
		//cout << int(round(alien(hi).first + (n - p)/2 * hi)) << "\n";

		vi used(n+2);
		pos cp = dpfreepos.back();
		while (cp.i != -1)
		{
			used[cp.i]=1;
			if (cp.taken) cp = dptakenpos[cp.i];
			else cp = dpfreepos[cp.i];
		}
		used.back() = 1;

		int cnt = 0;
		rep(i, n + 2) if (!used[i]) cnt++;
		cout << cnt << "\n";
		rep(i, n + 2) if(!used[i]) cout << cc[i].second << "\n";

	}

	return 0;
}
