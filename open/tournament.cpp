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
	int i, j, taken;
};
struct line // kx+m
{
	int k, m;
	pos from;
	int eval(int x) {
		return k * x + m; 
	}
	double isect(line other) { return double(other.m - m) / (k - other.k); }
};

signed main()
{
	fast();

	int n;
	while (cin >> n && n != 0)
	{
		vector<pair<int, string>> contestants;
		rep(i, n)
		{
			string name;
			int s;
			cin >> name >> s;
			contestants.emplace_back(s, name);
		}
		sort(contestants.rbegin(), contestants.rend());
		rep(i, n) contestants[i].first += 0.0000001 * i;
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
		int iglimit = p;
		
		vector<pair<int, string>> cc(contestants);
		cc.insert(cc.begin(), { 0, "LIGMA" });
		cc.push_back({ 0, "LIGMA" });
		pos defaultpos = pos({ -1,-1,-1 });
		vvi dptaken(n+2, vi(iglimit + 1, inf));
		vector<vector<pos>> dptakenpos(n + 2, vector<pos>(iglimit + 1, defaultpos));
		vvi dpfree(n+2, vi(iglimit + 1, inf));
		vector<vector<pos>> dpfreepos(n+2, vector<pos>(iglimit + 1, defaultpos));
		dptaken[0][0] = 0;
		
		vector<pair<int, pos>> smallesttaken(n + 2, { inf, pos({-1,-1,-1}) });
		smallesttaken[0] = { 0, pos({-2,-2,-2}) };
		vector<deque<line>> dplines(n + 2);
		
		line nullline = line({ 0,inf,defaultpos });
		auto add = [](deque<line>& cht, line l)
		{
			while (sz(cht)>1&&cht.back().isect(l)<cht[sz(cht)-2].isect(l))
			{
				cht.pop_back();
			}
			cht.push_back(l);
		};
		auto query = [nullline](deque<line>& cht, int x)
		{
			if (sz(cht) == 0) return nullline;
			while (sz(cht) > 1 && cht.back().eval(x)>cht[sz(cht)-2].eval(x))
			{
				cht.pop_front();
			}
			return cht.back();
		};

		repp(i, 1, n+2)
		{
			rep(j, min(i, iglimit + 1))
			{

				int ind = i - j - 1;
				line bestline = query(dplines[ind], cc[i].first);
				int bestv = bestline.eval(cc[i].first) + cc[i].first * cc[i].first;
				bestv = min(bestv, inf);
				dptaken[i][j] = bestv;
				dptakenpos[i][j] = bestline.from;
				dpfree[i][j] = smallesttaken[i-j-1].first;
				dpfreepos[i][j] = smallesttaken[i - j - 1].second;
				if (dptaken[i][j]<smallesttaken[i-j].first) smallesttaken[i-j] = make_pair(dptaken[i][j], pos({i,j,1}));
				line l = line({ -2 * cc[i].first, dpfree[i][j] + cc[i].first * cc[i].first, pos({i,j,0}) });
				add(dplines[i-j], l);
			}
		}
		
		set<string> used;
		pos cp = dpfreepos.back().back();
		while (cp.i!=-2)
		{
			if (1)
			{
				used.insert(cc[cp.i].second);
			}
			if (cp.taken) cp = dptakenpos[cp.i][cp.j];
			else cp = dpfreepos[cp.i][cp.j];
		}

		set<string> unused;
		repe(c, contestants) if (used.find(c.second) == used.end()) unused.insert(c.second);
		cout << sz(unused) << "\n";
		repe(c, unused) cout << c << "\n";
	}

	return 0;
}
