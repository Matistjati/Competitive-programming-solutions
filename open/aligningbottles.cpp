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

	vector<string> grid(4);
	rep(i, 4) cin >> grid[i];

	int k = 0;
	rep(i, 4) repe(c, grid[i]) k += c == 'o';
	auto get = [&](int i, int j)
	{
		return grid[i][j] == 'o';
	};
	int ans = inf;
	vector<string> best(4, string(6,' '));

	auto is_con = [k](vector<string>& grid)
	{
		p2 start;
		rep(i, 4) rep(j, 6) if (grid[i][j] == 'o') start = p2(i, j);
		int cnt = 0;

		vector<p2> dirs = { {0,1},{0,-1},{1,0}, {-1,0} };
		queue<p2> q;
		q.emplace(start);
		vvi vis(4, vi(6));
		while (sz(q))
		{
			p2 p = q.front();
			q.pop();
			if (vis[p.first][p.second]) continue;
			vis[p.first][p.second] = 1;
			cnt++;
			

			repe(dir, dirs)
			{
				p2 np = p2(p.first + dir.first, p.second + dir.second);
				if (np.first < 0 || np.second < 0 || np.first >= 4 || np.second >= 6) continue;
				if (grid[np.first][np.second] == '.') continue;
				q.emplace(np);
			}
		}

		return cnt == k;
	};

	rep(mask, 1 << 24)
	{
		if (popcount((unsigned long long)mask)!=k)
		{
			continue;
		}

		int cost = 0;

		vector<string> trial(4, string(6, ' '));
		rep(i, 4) rep(j, 6)
		{
			int ind = 1 << (i * 6 + j);
			if (mask & ind)
			{
				trial[i][j] = 'o';
			}
			else trial[i][j] = '.';
			cost += grid[i][j] != trial[i][j];
		}
		
		if (cost<ans)
		{
			if (is_con(trial))
			{
				ans = cost;
				best = trial;
			}
			
		}
	}
	rep(i, 4) cout << best[i] << "\n";

	return 0;
}
