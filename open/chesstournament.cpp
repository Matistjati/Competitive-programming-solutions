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

void toposort(int u, vi& vis, vi& order, vvi& adj)
{
	if (vis[u]) return;
	vis[u] = 1;

	repe(e, adj[u]) toposort(e, vis, order, adj);
	order.push_back(u);
}


signed main()
{
	fast();

	int n, m;
	cin >> n >> m;
	vvi adj(n);
	vvi radj(n);
	vector<tuple<int, int, char>> edges;
	rep(i, m)
	{
		int a, b;
		char c;
		cin >> a >> c >> b;
		if (c == '>') adj[a].push_back(b), radj[b].push_back(a);
		if (c == '<') adj[b].push_back(a), radj[a].push_back(b);
		if (c == '=') adj[a].push_back(b), adj[b].push_back(a), radj[a].push_back(b), radj[b].push_back(a);
		edges.emplace_back(a, b, c);
	}

	vi vis(n);
	vi order;
	rep(i, n) toposort(i, vis, order, adj);
	reverse(all(order));
	vis.assign(n, 0);
	vi whichcomp(n, -1);
	int compind = 0;
	repe(i, order)
	{
		if (vis[i]) continue;
		vi comp;
		toposort(i, vis, comp, radj);

		repe(u, comp) whichcomp[u] = compind;
		compind++;
	}
	auto die = []()
	{
		cout << "inconsistent";
		exit(0);
	};

	repe(e, edges)
	{
		int a, b;
		char c;
		tie(a, b, c) = e;
		if (c=='=')
		{
			if (whichcomp[a] != whichcomp[b]) die();
		}
		if (c=='>'||c=='<')
		{
			if (whichcomp[a] == whichcomp[b]) die();
		}
	}
	cout << "consistent";

	return 0;
}
