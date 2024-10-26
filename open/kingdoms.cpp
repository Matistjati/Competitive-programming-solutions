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

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vvi mat(n, vi(n));
		rep(i, n) rep(j, n) cin >> mat[i][j];
		vi dp(1 << n, 0);
		dp.back() = 1;
		for (int mask = sz(dp) - 1; mask >= 0; mask--)
		{
			if (dp[mask] == 0) continue;
			rep(i, n)
			{
				int s = 0;
				rep(j, n)
				{
					if (mask & (1 << j)) s += mat[i][j];
				}
				if (s>0)
				{
					dp[mask ^ (1 << i)] = 1;
				}
			}
		}
		int cnt = 0;
		rep(i, n)
		{
			if (dp[1 << i]) cout << i + 1 << " ", cnt++;
		}
		if (!cnt) cout << "0";
		cout << "\n";
	}


	return 0;
}
