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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Edmonds
{
	vvi flow;
	vvi cap;
	vi par;
	int n;
	int tot_flow = 0;

	void addEdge(int a, int b, int c)
	{
		cap[a][b] += c;
	}

	Edmonds(int n) : n(n), flow(n, vi(n)), cap(n, vi(n)), par(n) {}

	int bfs(int s, int t)
	{
		rep(i, n) par[i] = -1;
		par[s] = -2;
		queue<int> q;
		q.emplace(s);

		while (q.size())
		{
			int u = q.front(); q.pop();

			rep(e, n)
			{
				if (par[e] == -1 && flow[u][e] < cap[u][e])
				{
					par[e] = u;
					if (e == t) return 1;
					q.emplace(e);
				}
			}
		}

		return 0;
	}

	int augment(int s, int t) // find one augmenting path
	{
		if (bfs(s, t))
		{
			int f = inf;
			for (int cur = t; cur != s; cur = par[cur])
			{
				int p = par[cur];
				f = min(f, cap[p][cur]-flow[p][cur]);
			}
			tot_flow += f;
			for (int cur = t; cur != s; cur = par[cur])
			{
				int p = par[cur];
				flow[p][cur] += f;
				flow[cur][p] -= f;
			}

			return 1;
		}
		return 0;
	}

	int maxflow(int s, int t)
	{
		while (augment(s, t)) {}
		return tot_flow;
	}
};

signed main()
{
	fast();


	int n, m, q;
	cin >> n >> m >> q;
	Edmonds flow(n);
	rep(i, m)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		flow.addEdge(a, b, c);
		flow.addEdge(b, a, c);
	}

	cout << flow.maxflow(0, 1) << "\n";
	while (q--)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		flow.addEdge(a, b, c);
		flow.addEdge(b, a, c);
		cout << flow.maxflow(0, 1) << "\n";
	}


	return 0;
}
