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
		if (s >= g.size() || t >= g.size()) return;
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

	typedef tuple<int, int, int, int> p4;
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		int start, cnt, maxtime;
		cin >> start >> cnt >> maxtime;
		start--;
		int m;
		cin >> m;
		vi good;
		rep(i, m)
		{
			int u;
			cin >> u;
			u--;
			good.push_back(u);
		}
		int e;
		cin >> e;
		int nodecnt = n * (maxtime+1)+ 2;
		PushRelabel flow(nodecnt);
		vector<p4> edges;
		rep(i, e)
		{
			int a, b, p, t;
			cin >> a >> b >> p >> t;
			a--; b--;
			edges.emplace_back(a, b, p, t);
		}
		flow.addEdge(nodecnt - 2, start, cnt);
		repe(g, good) flow.addEdge(g + (maxtime) * n, nodecnt - 1, inf);
		rep(i, maxtime)
		{
			int base = i * n;
			rep(j, n)
			{
				flow.addEdge(j + base, j + base + n, inf);
			}
			repe(e, edges)
			{
				int newtime = i + get<3>(e);
				if (newtime > maxtime) continue;
				flow.addEdge(get<0>(e) + base, get<1>(e) + newtime * n, get<2>(e));
			}
		}
		cout << flow.calc(nodecnt - 2, nodecnt - 1) << "\n";
	}

	return 0;
}