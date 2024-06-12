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
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

typedef tuple<int, int, int> p3;
signed main()
{
	fast();

	int n, m;
	while (cin >> m >> n && n!=0)
	{
		vector<string> grid(n);
		rep(i, n) cin >> grid[i];
		vector<p2> ppl;
		vvi isspecial(n, vi(m, -1));
		rep(i, n)rep(j, m)
		{
			if (grid[i][j] >= 'A' && grid[i][j] <= 'D') isspecial[i][j] = sz(ppl),ppl.emplace_back(i, j),
				grid[i][j]='.';
		}
		vector<vvi> dist(4, vvi(n, vi(m)));
		vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
		rep(i, 4)
		{
			deque<p3> q;
			q.emplace_front(0, ppl[i].first, ppl[i].second);
			vvi vis(n, vi(m));
			while (q.size())
			{
				int d, a, b;
				tie(d, a, b) = q.front();
				q.pop_front();
				if (vis[a][b]) continue;
				vis[a][b] = 1;
				dist[i][a][b] = d;
				repe(dir, dirs)
				{
					p2 np = p2(dir.first + a, dir.second + b);
					if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= m || grid[np.first][np.second] == '#') continue;
					if (grid[np.first][np.second] == '.') q.emplace_front(d, np.first, np.second);
					else if (grid[np.first][np.second] == 'o') q.emplace_back(d + 1, np.first, np.second);
					else assert(0);
				}
			}
		}
		vector<vvi> cost(1 << 4, vvi(n,vi(m,inf)));
		rep(i, 4)
		{
			cost[1 << i][ppl[i].first][ppl[i].second] = 0;
		}

		rep(mask, 1 << 4)
		{
			if (mask+1==1<<4)
			{
				int ans = inf;
				rep(i, n)rep(j, m) ans = min(ans, cost[mask][i][j]);
				cout << ans << "\n";
			}
			priority_queue<p3> pq;
			bool any = 0;
			rep(i, n)
			{
				rep(j, m)
				{
					if (cost[mask][i][j] != inf) pq.emplace(-cost[mask][i][j], i, j);
				}
			}
			vvi vis(n, vi(m));
			while (pq.size())
			{
				int d, a, b;
				tie(d,a,b) = pq.top();
				pq.pop();
				if (vis[a][b]) continue;
				vis[a][b] = 1;

				rep(i, 4)
				{
					if ((mask & (1 << i)) == 0)
					{
						cost[mask | (1 << i)][a][b] = min(cost[mask | (1 << i)][a][b], -d+dist[i][a][b]-(grid[a][b]=='o'));
					}
				}

				repe(dir, dirs)
				{
					p2 np = p2(dir.first + a, dir.second + b);
					if (np.first < 0 || np.second < 0 || np.first >= n || np.second >= m || grid[np.first][np.second] == '#') continue;
					if (grid[np.first][np.second] == '.') pq.emplace(d, np.first, np.second);
					else if (grid[np.first][np.second] == 'o') pq.emplace(d - 1, np.first, np.second);
					else assert(0);
				}
			}
		}
	}

	return 0;
}
