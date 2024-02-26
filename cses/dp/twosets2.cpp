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

#define _LOCAL _DEBUG
#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int mod = 2 * int(1e9 + 7);
signed main()
{
	fast();

	int n;
	cin >> n;
	int v = n * (n + 1) / 2;
	if (v % 2 == 1)
	{
		cout << 0;
		return 0;
	}

	vi dp(n * n);
	dp[0] = 1;

	repp(i, 1, n + 1)
	{
		for (int j = sz(dp) - 1; j >= 0; j--)
		{
			if (j - i < 0) break;
			dp[j] = (dp[j] + dp[j - i]) % mod;
		}
	}
	cout << dp[v / 2] / 2;

	return 0;
}
