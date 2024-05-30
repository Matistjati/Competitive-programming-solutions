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

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
	fast();

	int n, m;
	cin >> n >> m;
	vector<string> grid(n);
	rep(i, n) cin >> grid[i];

	queue<p2> q;
	rep(i, n)
	{
		rep(j, m)
		{
			if (grid[i][j] == 'V') q.emplace(i, j);
		}
	}

	vvi vis(n, vi(m));
	while (q.size())
	{
		p2 p = q.front();
		q.pop();

		grid[p.first][p.second] = 'V';
		if (vis[p.first][p.second]) continue;
		vis[p.first][p.second] = 1;

		if (p.first + 1 >= n) continue;
		if (grid[p.first + 1][p.second] == '#')
		{
			// spread
			if (p.second + 1 < m && grid[p.first][p.second + 1] != '#') q.emplace(p.first, p.second + 1);
			if (p.second - 1 >= 0 && grid[p.first][p.second - 1] != '#') q.emplace(p.first, p.second - 1);
		}
		else q.emplace(p.first + 1, p.second);
	}
	

	repe(row, grid) cout << row << "\n";
	
	return 0;
}
