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

	map<char, p2> dir;
	dir['S'] = p2(1, 0);
	dir['W'] = p2(0, -1);
	dir['E'] = p2(0, 1);
	dir['N'] = p2(-1, 0);
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;

		map<p2, int> graph;
		p2 pos = p2(0, 0);

		vvi adj;
		auto add_pos = [&](p2 p)
			{
				if (!graph.count(p)) graph[p] = sz(graph), adj.push_back({});
			};
		add_pos(pos);

		rep(i, n)
		{
			char d;
			cin >> d;
			p2 delta = dir[d];
			p2 np = { pos.first + delta.first, pos.second + delta.second };
			add_pos(np);
			int cind = graph[pos];
			int nind = graph[np];
			adj[cind].push_back(nind);
			adj[nind].push_back(cind);
			pos = np;
		}
		int t = graph[pos];
		queue<p2> q;
		vi vis(sz(adj));
		q.emplace(0, 0);
		while (sz(q))
		{
			int d, u;
			tie(d, u) = q.front();
			q.pop();

			if (vis[u]) continue;
			vis[u] = 1;

			if (u == t)
			{
				cout << d << "\n";
				break;
			}

			repe(e, adj[u]) q.emplace(d + 1, e);
		}
	}

	return 0;
}
