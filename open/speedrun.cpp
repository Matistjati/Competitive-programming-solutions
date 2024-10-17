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

	int g, n;
	cin >> g >> n;
	vector<p2> tasks(n);
	rep(i, n) cin >> tasks[i].first >> tasks[i].second;
	sort(all(tasks), [](p2 a, p2 b)
		{
			return a.second < b.second;
		});
	int s = 0;
	int l = -1;
	repe(t, tasks)
	{
		if (t.first >= l)
		{
			l = t.second;
			s++;
		}
	}

	cout << (s >= g ? "YES" : "NO");

	return 0;
}
