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


struct PushRelabel {
	struct Edge {
		int dest, back;
		ll f, c;
	};
	vector<vector<Edge>> g;
	vector<ll> ec;
	vector<Edge*> cur;
	vector<vi> hs; vi H;
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n) {}

	void addEdge(int s, int t, ll cap, ll rcap = 0) {
		if (s == t) return;
		g[s].push_back({ t, sz(g[t]), 0, cap });
		g[t].push_back({ s, sz(g[s]) - 1, 0, rcap });
	}

	void addFlow(Edge& e, ll f) {
		Edge& back = g[e.dest][e.back];
		if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
		e.f += f; e.c -= f; ec[e.dest] += f;
		back.f -= f; back.c += f; ec[back.dest] -= f;
	}
	ll calc(int s, int t) {
		int v = sz(g); H[s] = v; ec[t] = 1;
		vi co(2 * v); co[0] = v - 1;
		repp(i, 0, v) cur[i] = g[i].data();
		for (Edge& e : g[s]) addFlow(e, e.c);

		for (int hi = 0;;) {
			while (hs[hi].empty()) if (!hi--) return -ec[s];
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ec[u] > 0)  // discharge u
				if (cur[u] == g[u].data() + sz(g[u])) {
					H[u] = 1e9;
					for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest] + 1)
						H[u] = H[e.dest] + 1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						repp(i, 0, v) if (hi < H[i] && H[i] < v)
						--co[H[i]], H[i] = v + 1;
					hi = H[u];
				}
				else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
					addFlow(*cur[u], min(ec[u], cur[u]->c));
				else ++cur[u];
		}
	}
	bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

signed main()
{
	fast();

	int n, m, c;
	cin >> n >> m >> c;
	vector<vector<p2>> edges(n);
	vector<tuple<int, int, int>> edgelist;
	rep(i, m)
	{
		int a, b, d;
		cin >> a >> b >> d;
		a--; b--;
		edges[a].emplace_back(b, d);
		edges[b].emplace_back(a, d);
		edgelist.emplace_back(a, b, d);
	}

	vi dist(n, inf);
	vi vis(n);
	priority_queue<p2> pq;
	pq.emplace(0, 0);

	while (pq.size())
	{
		int d, u;
		tie(d, u) = pq.top();
		pq.pop();

		if (vis[u]) continue;
		vis[u] = 1;
		dist[u] = -d;

		repe(e, edges[u])
		{
			int newd = d - e.second;
			if (-newd<dist[e.first])
			{
				dist[e.first] = -newd;
				pq.emplace(newd, e.first);
			}
		}
	}

	
	map<int, vi> distgroups;
	rep(i, c)
	{
		int u;
		cin >> u;
		u--;
		distgroups[dist[u]].push_back(u);
	}
	int ans = 0;
	repe(g, distgroups)
	{
		PushRelabel flow(n + 1);
		repe(e, edgelist)
		{
			int a, b, d;
			tie(a, b, d) = e;
			if (dist[a] + d == dist[b])
			{
				flow.addEdge(b, a, 1);
			}
			if (dist[b] + d == dist[a])
			{
				flow.addEdge(a, b, 1);
			}
		}
		repe(u, g.second) flow.addEdge(n, u, 1);
		ans += flow.calc(n, 0);
	}

	cout << ans;

	return 0;
}
