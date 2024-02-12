#pragma GCC optimize("Ofast,inline,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")//,tune=native")

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
#define per(i, high) for (int i = high-1; i >= 0; i--)

#define _LOCAL _MSC_VER
#if _LOCAL > 0
#define deb __debugbreak();
#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
#define clz(x) _lzcnt_u32(x)
#else
#define clz(x) __builtin_clz(x)
#define deb ;
#define popcount(x) __builtin_popcountll(x)
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#ifdef _DEBUG
#define debassert(expr) if(!(expr)) deb;
#else
#define debassert(expr) ;
#endif

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]


int precomp1[15][15][int(1e5)];
int precomp2[15][15][int(1e5)];

signed main()
{
	fast();

	string s;
	cin >> s;

	map<char, int> gind;
	vvi groups;
	vvi activegroup;
	int n = sz(s);
	rep(i, n)
	{
		if (!setcontains(gind, s[i])) gind[s[i]] = gind.size(), groups.push_back({});
		groups[gind[s[i]]].push_back(i);
	}
	int g = sz(groups);

	vi groupsz(g);
	rep(i, g)groupsz[i] = sz(groups[i]);
	activegroup.resize(g, vi(n));
	rep(i, g) repe(v, groups[i]) activegroup[i][v] = 1;

	double ans = inf;

	vector<double> exppl(n + 1);
	double v = 0;
	double addend = 0;
	repp(i, 1, n + 1)
	{
		v += addend;
		addend += 0.5;
		exppl[i] = v;
	}

	memset(precomp1, 0, sizeof(precomp1));
	memset(precomp2, 0, sizeof(precomp2));

	rep(a, g)
	{
		rep(b, g)
		{
			int pref = 0;
			int t = 0;
			rep(i, n)
			{
				if (activegroup[a][i]) pref += 1;
				if (activegroup[b][i]) t += pref;
				precomp1[a][b][i] = t;
			}

			pref = 0;
			t = 0;
			per(i, n)
			{
				if (activegroup[a][i]) pref += 1;
				if (activegroup[b][i]) t += pref;
				precomp2[a][b][i] = t;
			}
		}
	}

	auto get = [&](int mask, int groupid, int p)
	{
		int mid = (p == groupsz[groupid] ? n : groups[groupid][p]);

		double cost = 0;

		rep(j, g)
		{
			if ((mask & (1 << j)) == 0) continue;
			if (mid) cost += precomp1[j][groupid][mid - 1];
			if (mid < n) cost += precomp2[j][groupid][mid];
		}
		cost += exppl[p] + exppl[groupsz[groupid] - p];

		return cost;
	};

	auto solvegroup = [&](int mask, int groupid)
	{
		double best = inf;

		int lo = 0;
		int hi = groupsz[groupid] + 1;

		while (hi - lo > 5)
		{
			int l = lo + (hi - lo) / 3;
			int r = hi - (hi - lo) / 3;
			if (get(mask, groupid, l) > get(mask, groupid, r))
			{
				lo = l;
			}
			else hi = r;
		}
		int ret = lo;
		repp(l, lo, min(groupsz[groupid] + 1, hi + 2)) if (get(mask, groupid, l) < get(mask, groupid, ret)) ret = l;

		return get(mask, groupid, ret);
	};

	vector<double> dp(1 << g, inf);
	dp[0] = 0;
	rep(mask, 1 << g)
	{
		rep(i, g)
		{
			if (mask & (1 << i)) continue;
			dp[mask | (1 << i)] = min(dp[mask | (1 << i)], dp[mask] + solvegroup(mask, i));
		}
	}

	cout << fixed << setprecision(15) << dp.back();

	return 0;
}
