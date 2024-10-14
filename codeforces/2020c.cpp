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
	int b, c, d;
	cin >> b >> c >> d;

	auto die = []()
	{
		cout << -1 << "\n";
	};

	int ans = 0;
	rep(i, 62)
	{
		int bi = !!(b & (1LL << i));
		int ci = !!(c & (1LL << i));
		int di = !!(d & (1LL << i));
		if (bi==0&&ci==0)
		{
			if (di) ans += 1LL << i;
		}
		else if (bi==1&&ci==0)
		{
			if (!di) return die();
		}
		else if (bi==0&&ci==1)
		{
			if (di) return die();
		}
		else
		{
			if (!di) ans += 1LL << i;
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
