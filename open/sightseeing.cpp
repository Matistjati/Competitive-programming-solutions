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

struct edge
{
	int from, to, lo, hi;
};
typedef PushRelabel flowAlgorithm;
// Returns null if no feasible flow exists with given lower bounds
// To find min flow satisfying constraints, binary search for smallest capacity giving feasible solution
flowAlgorithm* lowerbound_flow(vector<edge>& edges, int n)
{
	flowAlgorithm* flow = new flowAlgorithm(n + 2);
	vi outflow(n), inflow(n);
	repe(e, edges)
	{
		outflow[e.from] += e.lo;
		inflow[e.to] += e.lo;
		flow->addEdge(e.from, e.to, e.hi - e.lo);
	}
	rep(i, n)
	{
		flow->addEdge(n, i, inflow[i]);
		flow->addEdge(i, n + 1, outflow[i]);
	}

	return flow->calc(n, n + 1) == accumulate(all(outflow), 0) ? flow : nullptr;
}

signed main()
{
    fast();

    int n, m;
    cin >> n >> m;
	vector<edge> edges;
	rep(i, n)
	{
		edge e = { i * 2,i * 2 + 1,1,1 };
		edges.emplace_back(e);
	}

	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		edge e = { a*2+1, b * 2,0,1 };
		edges.emplace_back(e);
	}

	PushRelabel* flow = lowerbound_flow(edges, 2 * n);
	if (!flow)
	{
		cout << "Yeah!";
	}
	else
	{
		vvi groups;
		vi vis(n);
		rep(i, n)
		{
			if (vis[i]) continue;
			groups.push_back({});
			int start = 2 * i+1;
			int u = start;
			do
			{
				vis[u / 2] = 1;
				groups.back().push_back(u/2);
				repe(e, flow->g[u])
				{
					if (e.f&&e.dest<2*n)
					{
						e.f--;
						u = e.dest + 1;
					}
				}
			} while (u!=start);
		}
		cout << sz(groups) << "\n";
		repe(g, groups)
		{
			cout << sz(g) << "\n";
			repe(u, g) cout << u << "\n";
		}
	}

    return 0;
}
