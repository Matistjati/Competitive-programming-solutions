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
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
	fast();

	int r, c, s;
	cin >> r >> c >> s;
	p2 start, goal;
	cin >> start.first >> start.second;
	cin >> goal.first >> goal.second;
	start.first--; start.second--;
	goal.first--; goal.second--;
	vector<string> grid(r);
	rep(i, r)
	{
		cin >> grid[i];
	}

	queue<p2> whiteq;
	whiteq.push(start);
	int ans = 0;
	vvi visw(r, vi(c));
	vvi visb(r, vi(c));
	vector<p2> dirs = { {1,0},{0,1},{-1,0},{0,-1} };
	vector<p2> dirs2 = { {1,0},{0,1},{-1,0},{0,-1}, {1,1},{1,-1},{-1,1},{-1,-1} };
	typedef tuple<int, int, int> p3;
	while (true)
	{
		queue<p3> blackq;
		while (sz(whiteq))
		{
			p2 p = whiteq.front();
			whiteq.pop();

			if (visw[p.first][p.second]) continue;
			visw[p.first][p.second] = 1;

			if (p == goal)
			{
				cout << ans;
				return 0;
			}

			repe(dir, dirs)
			{
				p2 np = { p.first + dir.first,p.second + dir.second };
				if (np.first < 0 || np.second < 0 || np.first >= r || np.second >= c) continue;
				if (grid[np.first][np.second] == '#') blackq.emplace(1, np.first, np.second);
				else whiteq.emplace(np);
			}
		}


		while (sz(blackq))
		{
			int d, a, b;
			tie(d, a, b) = blackq.front();
			blackq.pop();


			if (d > s) continue;
			if (visb[a][b]) continue;
			visb[a][b] = 1;

			grid[a][b] = '.';
			whiteq.emplace(a, b);

			repe(dir, dirs2)
			{
				p2 np = { a + dir.first, b + dir.second };
				if (np.first < 0 || np.second < 0 || np.first >= r || np.second >= c) continue;
				blackq.emplace(d + 1, np.first, np.second);
			}
		}

		ans++;
	}


	return 0;
}