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

	int r, s, m;
	cin >> r >> s >> m;

	vector<p2> edges;
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		edges.emplace_back(a, b);
	}


	int nodecnt = r + s + m + 2;
	auto getnetwork = [&](int lim)
	{
		PushRelabel flow(nodecnt);

		rep(i, m) flow.addEdge(nodecnt - 2, i, 1);
		rep(i, sz(edges))
		{
			int a, b;
			tie(a, b) = edges[i];
			flow.addEdge(i, a + m, 1);
			flow.addEdge(i, b + m + r, 1);
		}
		repp(i, m, nodecnt - 2)
		{
			flow.addEdge(i, nodecnt - 1, lim);
		}
		return flow;
	};

	int lo = 0;
	int hi = m;
	while (lo + 1 < hi)
	{
		int mid = (lo + hi) / 2;
		int f = getnetwork(mid).calc(nodecnt - 2, nodecnt - 1);
		if (f == m)
		{
			hi = mid;
		}
		else lo = mid;
	}
	PushRelabel network = getnetwork(hi);
	network.calc(nodecnt - 2, nodecnt - 1);
	rep(i, m)
	{
		repe(e, network.g[i])
		{
			if (e.f > 0)
			{
				if (e.dest < r + m) cout << "INDV " << e.dest - m + 1 << "\n";
				else cout << "CORP " << e.dest - m - r + 1 << "\n";
			}
		}
	}

	return 0;
}
