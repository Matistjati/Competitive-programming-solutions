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

string goal;
vector<string> grid;
vector<p2> dirs = { {0,1},{1,0},{0,-1},{-1,0} };
p2 where[4][50][50];
int best(int r, int c, int ind)
{
	if (ind==sz(goal))
	{
		return 0;
	}

	int ret = inf;
	if (grid[r][c]==goal[ind])
	{
		ret = min(ret, 1 + best(r, c, ind + 1));
	}

	rep(d, 4)
	{
		p2 np = where[d][r][c];
		if (np.first == -1) continue;
		ret = min(ret, 1 + best(np.first, np.second, ind));
	}

	return ret;
}

signed main()
{
	fast();

	int r, c;
	cin >> r >> c;
	grid.resize(r);
	rep(i, r) cin >> grid[i];

	rep(i, r) rep(j, c) rep(d,4)
	{
		p2 p = p2(i, j);
		char cha = grid[i][j];
		bool good = 1;
		while (grid[p.first][p.second]== cha)
		{
			p.first += dirs[d].first;
			p.second += dirs[d].second;

			if (p.first < 0 || p.second < 0 || p.first >= r || p.second >= c)
			{
				good = 0;
				break;
			}
		}
		if (good)
		{
			where[d][i][j] = p;
		}
		else where[d][i][j] = p2(-1, -1);
	}

	cin >> goal;
	goal += '*';
	queue<tuple<int, int, int, int>> q;
	q.emplace(0, 0, 0, 0);
	int vis[50][50][int(1e4)+10];
	memset(vis, 0, sizeof(vis));
	while (sz(q))
	{
		int r, c, ind, dist;
		tie(r, c, ind, dist) = q.front();
		q.pop();

		if (vis[r][c][ind]) continue;
		vis[r][c][ind] = 1;

		if (ind==sz(goal))
		{
			cout << dist;
			return 0;
		}

		if (grid[r][c]==goal[ind])
		{
			q.emplace(r, c, ind + 1, dist + 1);
		}

		rep(d, 4)
		{
			p2 np = where[d][r][c];
			if (np.first == -1) continue;
			q.emplace(np.first, np.second, ind, dist+1);
		}
	}

	return 0;
}
