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

#define _LOCAL _DEBUG
#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Edmonds
{
	int n;
	vvi flow;
	vvi capacity;
	vi par;

	Edmonds(int n) : n(n), flow(n, vi(n)), capacity(n, vi(n)), par(n) {}

	bool path(int a, int b)
	{
		queue<p2> q;
		q.emplace(a, -2);
		rep(i, n)par[i] = -1;

		while (q.size())
		{
			int u, p;
			tie(u, p) = q.front(); q.pop();

			if (par[u] != -1) continue;
			par[u] = p;

			if (u == b) return 1;

			rep(e, n)
			{
				if (flow[u][e] < capacity[u][e])
				{
					q.emplace(e, u);
				}
			}
		}
		return 0;
	}

	void addedge(int a, int b, int cap)
	{
		capacity[a][b] = cap;
	}

	int maxflow(int a, int b)
	{
		int totflow = 0;
		while (path(a, b))
		{
			int flowsent = inf;
			int u = b;
			while (par[u] != -2)
			{
				flowsent = min(flowsent, capacity[par[u]][u] - flow[par[u]][u]);
				u = par[u];
			}
			totflow += flowsent;
			u = b;
			while (par[u] != -2)
			{
				flow[par[u]][u] += flowsent;
				flow[u][par[u]] -= flowsent;
				u = par[u];
			}
		}
		return totflow;
	}

	vi getpath(int a, int b)
	{
		queue<p2> q;
		q.emplace(a, -2);
		rep(i, n)par[i] = -1;

		while (q.size())
		{
			int u, p;
			tie(u, p) = q.front(); q.pop();

			if (par[u] != -1) continue;
			par[u] = p;

			if (u == b) break;

			rep(e, n)
			{
				if (flow[u][e] > 0)
				{
					q.emplace(e, u);
				}
			}
		}

		vi path;
		int u = b;
		while (par[u] != -2)
		{
			path.push_back(u);
			flow[par[u]][u] -= 1;
			u = par[u];
		}
		path.push_back(u);
		reverse(all(path));
		return path;
	}
};

signed main()
{
	fast();

	int n, m;
	cin >> n >> m;

	Edmonds flow(n);
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		flow.addedge(a, b, 1);
	}

	int f = flow.maxflow(0, n - 1);
	cout << f << "\n";

	rep(i, f)
	{
		vi path = flow.getpath(0, n - 1);
		cout << path.size() << "\n";
		repe(v, path) cout << v + 1 << " ";
		cout << "\n";
	}

	return 0;
}
