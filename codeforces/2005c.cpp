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

const vector<char> narek = { 'n','a','r','e','k' };

vector<string> grid;
int n, m;
int dp[6][1010][1010];
int isnarek[255];
int best(int sind, int i, int p)
{
	if (sind>=n)
	{
		return -p;
	}

	int& v = dp[p][sind + 1][i];
	if (v != -inf) return v;

	int ret = -inf+10;

	if (i==m)
	{
		ret = max(ret, best(sind + 1, 0, p));
		ret = max(ret, best(sind + 1, m, p));
	}
	else
	{
		bool any = isnarek[grid[sind][i]];
		if (any)
		{
			if (grid[sind][i] == narek[p])
			{
				ret = max(ret, ((p+1) == sz(narek) ? 5 : 0) + best(sind, i + 1, (p + 1) % sz(narek)));
			}
			else ret = max(ret, -1 + best(sind, i + 1, p));
		}
		else ret = max(ret, best(sind, i + 1, p));
	}

	return v=ret;
}

void solve()
{
	cin >> n >> m;
	grid.resize(0);
	grid.resize(n);
	rep(i, n) cin >> grid[i];
	rep(p, 6) rep(i, n+4) rep(j, m+4) dp[p][i][j] = -inf;
	cout << best(-1, m, 0) << "\n";
}

signed main()
{
	fast();

	isnarek['n'] = 1;
	isnarek['a'] = 1;
	isnarek['r'] = 1;
	isnarek['e'] = 1;
	isnarek['k'] = 1;

	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}

	return 0;
}
