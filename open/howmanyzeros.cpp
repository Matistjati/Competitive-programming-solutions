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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int dp[40][40][2][2];
int cnt(int i, int numzero, bool unlimited, bool nonzero, vi& lim)
{
	if (i == sz(lim)) return numzero;

	int& v = dp[i][numzero][unlimited][nonzero];
	if (v != -1) return v;

	int ret = 0;

	int hi = unlimited ? 10 : lim[i]+1;
	rep(d, hi)
	{
		ret += cnt(i + 1, numzero + (d==0&&nonzero), d + 1 < hi || unlimited, nonzero || d > 0, lim);
	}

	return v=ret;
}

int count(int r)
{
	if (r < 0) return 0;
	string s = to_string(r);
	vi lim(sz(s));
	rep(i, sz(s)) lim[i] = s[i] - '0';
	
	memset(dp, -1, sizeof(dp));
	return cnt(0, 0, 0, 0, lim);
}

signed main()
{
	fast();

	int l, r;
	while (cin >> l >> r && l!=-1)
	{
		cout << (count(r) - count(l - 1)+(l==0)) << "\n";
	}

	return 0;
}
