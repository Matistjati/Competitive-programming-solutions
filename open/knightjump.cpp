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

	int r;
	cin >> r;
	vector<string> grid(r);
	rep(i, r) cin >> grid[i];

	p2 start;
	rep(i, r) rep(j, r) if (grid[i][j] == 'K') start = p2(i, j);

	queue<pair<int, p2>> q;
	q.emplace(0, start);
	vvi vis(r, vi(r));
	vector<p2> dirs = { {1,2},{2,1},{-1,2},{-2,1},{1,-2},{2,-1},{-1,-2},{-2,-1} };
	while (sz(q))
	{
		int d;
		p2 pos;
		tie(d, pos) = q.front();
		q.pop();

		if (vis[pos.first][pos.second]) continue;
		vis[pos.first][pos.second] = 1;

		if (pos==p2(0,0))
		{
			cout << d;
			return 0;
		}

		repe(dir, dirs)
		{
			p2 np = p2(pos.first + dir.first, pos.second + dir.second);

			if (np.first < 0 || np.second < 0 || np.first >= r || np.second >= r || grid[np.first][np.second] == '#') continue;
			q.emplace(d + 1, np);
		}
	}
	cout << -1;

	return 0;
}
