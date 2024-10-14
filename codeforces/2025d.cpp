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

void solve()
{
	int n, k;
	cin >> n >> k;

	map<int, int> occ;
	rep(i, n)
	{
		int x;
		cin >> x;
		occ[x]++;
	}

	int ans = 0;
	set<int> seen;
	repe(u, occ)
	{
		if (seen.find(u.first)!=seen.end())
		{
			continue;
		}
		
		vi interval;
		int x = u.first;
		while (occ.find(x)!=occ.end())
		{
			seen.insert(x);
			interval.push_back(occ[x]);
			x++;
		}


		int start = 0;
		rep(i, min(sz(interval), k)) start += interval[i];
		ans = max(ans, start);
		repp(i,k,sz(interval))
		{
			start += interval[i] - interval[i - k];
			ans = max(ans, start);
		}
		

		
	}
	cout << ans << "\n";
}

signed main()
{
	fast();

	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}

	return 0;
}
