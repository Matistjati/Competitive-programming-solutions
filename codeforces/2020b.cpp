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
	int k;
	cin >> k;

	int lo = 0;
	int hi = int(4e18);
	while (lo+1<hi)
	{
		int mid = (lo + hi) / 2;
		int u = mid - floorl(sqrtl(mid));
		if (u >= k)
		{
			hi = mid;
		}
		else lo = mid;
	}
	cout << hi << "\n";
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
