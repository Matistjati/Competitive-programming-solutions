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

	int l, n;
	cin >> l >> n;

	vector<p2> intervals;
	rep(i, n)
	{
		int a, b;
		cin >> a >> b;
		intervals.emplace_back(a, b);
	}

	int ans = 0;

	sort(all(intervals));
	priority_queue<p2> waiting;
	int bestdp = 0;
	rep(i, n)
	{
		int a, b;
		tie(a, b) = intervals[i];
		while (sz(waiting)&&-waiting.top().first<a)
		{
			bestdp = max(bestdp, waiting.top().second);
			waiting.pop();
		}

		int v = b - a + 1 + bestdp;
		ans = max(ans, v);
		waiting.emplace(-b, v);
	}

	cout << l - ans;

	return 0;
}
