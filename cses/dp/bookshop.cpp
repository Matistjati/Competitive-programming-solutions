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
#define assert(x) if (!(x)) __debugbreak()
#endif

struct book
{
	int cost, profit;
};


signed main()
{
	fast();

	int n, x;
	cin >> n >> x;
	vector<book> books(n);
	rep(i, n) cin >> books[i].cost;
	rep(i, n) cin >> books[i].profit;

	vi dp(x + 1);
	auto addtodp = [&](int p, int c)
	{
		for (int i = x; i >= 0; i--)
		{
			if (i - c < 0) break;
			dp[i] = max(dp[i], p + dp[i - c]);
		}
	};
	rep(i, n)
	{
		book it = books[i];
		addtodp(it.profit, it.cost);
	}
	cout << *max_element(all(dp));

	return 0;
}
