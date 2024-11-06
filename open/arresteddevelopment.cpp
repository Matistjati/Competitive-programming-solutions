#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
const int inf = int(1e9);// int(1e18);

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
	cin >> n;

	vi dp(n*int(1e5+20), inf);
	dp[0] = 0;
	// dp[dev a time] = min dev b time

	rep(i, n)
	{
		int a, b;
		cin >> a >> b;

		for (int j = sz(dp) - 1; j >= 0; j--)
		{
			if (j >= a) dp[j] = min(dp[j] + b, dp[j - a]);
			else dp[j] += b;
		}

	}

	int ans = inf;
	rep(i, sz(dp))
	{
		ans = min(ans, max(i, dp[i]));
	}
	cout << ans;

	return 0;
}
