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
		rep(i, v) cur[i] = g[i].data();
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
						rep(i, v) if (hi < H[i] && H[i] < v)
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
	cin >> m >> n >> c;
	vector<string> grid(n);
	rep(i, n) cin >> grid[i];
	map<int, int> cost;
	cost['.'] = inf;
	cost['B'] = inf;
	rep(i, c)
	{
		int v;
		cin >> v;
		cost[i + 'a'] = v;
	}

	auto getind = [&](int i, int j)
	{
		return i * m + j;
	};

	int gridsz = n * m;
	int numnodes = gridsz * 2 + 2;
	PushRelabel flow(numnodes);
	rep(i, m) flow.addEdge(getind(0, i), numnodes - 1, inf);
	rep(i, m) flow.addEdge(getind(n - 1, i), numnodes - 1, inf);
	repp(i, 1, n - 1) flow.addEdge(getind(i, 0), numnodes - 1, inf);
	repp(i, 1, n - 1) flow.addEdge(getind(i, m - 1), numnodes - 1, inf);

	vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

	rep(i, n) rep(j, m)
	{
		flow.addEdge(getind(i, j) + gridsz, getind(i, j), cost[grid[i][j]]);
		if (grid[i][j] == 'B')
		{
			flow.addEdge(numnodes - 2, getind(i, j), inf);
		}
		repe(dir, dirs)
		{
			p2 p = { i + dir.first,j + dir.second };
			if (p.first < 0 || p.second < 0 || p.first >= n || p.second >= m) continue;
			flow.addEdge(getind(i, j), getind(p.first, p.second) + gridsz, inf);
		}
	}

	int ans = flow.calc(numnodes - 2, numnodes - 1);
	if (ans == inf) cout << -1;
	else cout << ans;

	return 0;
}