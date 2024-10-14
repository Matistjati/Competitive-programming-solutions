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

string top, bot;

int dp[3][int(1e5 + 10)];

int good(char a, char b, char c)
{
	int g = (a == 'A') + (b == 'A') + (c == 'A');
	return g>1;
}

int best(int i, int delta)
{
	if (i==sz(top))
	{
		return 0;
	}

	int& v = dp[delta + 1][i];
	if (v != -1) return v;

	int ret = 0;
	// both 3
	if (i+max(0LL,delta)+2<sz(top))
	{
		int p = good(top[i], top[i + 1], top[i + 2]);
		p += good(bot[i + delta], bot[i + delta + 1], bot[i + delta + 2]);
		ret = max(ret, p+best(i+3,delta));
	}

	if (delta==0)
	{
		ret = max(ret, good(top[i], bot[i], top[i + 1]) + best(i + 2, -1));
		ret = max(ret, good(top[i], bot[i], bot[i + 1]) + best(i + 1, 1));
	}

	if (delta==1)
	{
		ret = max(ret, good(top[i], bot[i+1], top[i + 1]) + best(i + 2, 0));
	}
	
	if (delta==-1)
	{
		ret = max(ret, good(top[i], bot[i-1], bot[i]) + best(i + 1, 0));
	}
	
	return v = ret;
}

void solve()
{
	int n;
	cin >> n;

	rep(a, 3) rep(j, n) dp[a][j] = -1;
	
	cin >> top >> bot;

	cout << best(0, 0) << "\n";
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
