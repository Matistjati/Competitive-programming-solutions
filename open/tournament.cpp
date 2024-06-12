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

inline double square(double x) { return x * x; }

signed main()
{
	fast();

	int n;
	while (cin >> n && n != 0)
	{
		vector<pair<double, string>> contestants(n);
		rep(i, n)
		{
			cin >> contestants[i].second >> contestants[i].first;
		}
		sort(all(contestants), [](pair<double, string>& a, pair<double, string>& b)
			{
				return a.first > b.first;
			});

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
		assert((n - p) % 2 == 0);
		int yesc = (n - p) / 2;
		// make all number of knights reachable by adding small epsilon, breaking ties
		uniform_real_distribution<double> dist(1e-7, 0.1);
		mt19937 rng;
		rep(i, sz(contestants)) contestants[i].first += dist(rng);

		vi from(n + 1);
		vector<pair<double, int>> dp(n + 1);
		auto alien = [&](double lambda)
		{
			dp[0] = { 0,0 };
			repp(i, 1, n+1)
			{
				dp[i] = dp[i - 1];
				from[i] = 1;
				if (i > 1)
				{
					double c = dp[i - 2].first + square(contestants[i - 2].first - contestants[i - 1].first)-lambda;
					if (c < dp[i].first) dp[i] = { c, dp[i - 2].second + 1 }, from[i]=2;
				}
			}
			return dp.back();
		};

		double lo = 0;
		double hi = 1e8;
		rep(i, 50)
		{
			double mid = (hi + lo) / 2;
			if (alien(mid).second >= yesc) hi = mid;
			else lo = mid;
		}
		alien(hi);
		
		vi used(n);
		int pos = n;
		do
		{
			if (from[pos] == 1) pos--;
			else if (from[pos]==2) used[pos -1]=1,used[pos -2]=1, pos -=2;
			else assert(0);
		} while (pos != 0);

		int cnt = 0;
		rep(i, n) if (!used[i]) cnt++;
		assert(cnt == p);
		cout << cnt << "\n";
		rep(i, n) if (!used[i]) cout << contestants[i].second << "\n";
	}

	return 0;
}
