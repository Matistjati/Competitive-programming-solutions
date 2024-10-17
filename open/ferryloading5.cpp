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

signed main()
{
	fast();

	int n;
	bool first = 1;
	while (cin >> n && n)
	{
		if (!first) cout << "\n";
		first = 0;
		vector<pair<int,double>> vehicles(n);
		rep(i, n) cin >> vehicles[i].second, vehicles[i].first=i;

		mt19937 rng(10);

		double t = 0;
		repe(v, vehicles) t += v.second;
		t /= 2;
		vi sol;
		double best = -1;

		// this really should not work....
		rep(i, 1000)
		{
			vi taken;
			double tot = 0;
			shuffle(all(vehicles), rng);
			rep(j, n)
			{
				if (tot+vehicles[j].second<=t)
				{
					tot += vehicles[j].second;
					taken.push_back(vehicles[j].first);
				}
			}
			if (tot>best)
			{
				best = tot;
				sol = taken;
			}
		}
		rep(i, sz(sol))
		{
			cout << sol[i] + 1;
			if (i + 1 != sz(sol)) cout << " ";
		}
		
	}

	return 0;
}
