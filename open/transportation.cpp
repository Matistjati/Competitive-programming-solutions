#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e12);

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

	int s, r, f, t;
	cin >> s >> r >> f >> t;

	int numnodes = s*2 + 2 * t + 2;
	PushRelabel flow(numnodes);
	map<string, int> state_ind;
	int factory_base = s;
	int transport_base = s+s;

	rep(i, r)
	{
		string state;
		cin >> state;
		if (state_ind.find(state) == state_ind.end()) state_ind[state] = sz(state_ind);
		flow.addEdge(numnodes - 2, state_ind[state], 1);
	}
	rep(i, f)
	{
		string state;
		cin >> state;
		if (state_ind.find(state) == state_ind.end()) state_ind[state] = sz(state_ind);
		flow.addEdge(factory_base+state_ind[state], numnodes-1, 1);
	}
	
	rep(i, t)
	{
		int k;
		cin >> k;
		flow.addEdge(transport_base + i * 2, transport_base + i * 2 + 1, 1);
		rep(j, k)
		{
			string state;
			cin >> state;
			if (state_ind.find(state) == state_ind.end()) state_ind[state] = sz(state_ind);
			int ind = state_ind[state];
			flow.addEdge(ind, transport_base + i * 2, 1);
			flow.addEdge(factory_base+ind, transport_base + i * 2, 1);
			flow.addEdge(transport_base + i * 2+1, ind+factory_base, 1);
			flow.addEdge(transport_base + i * 2+1, ind, 1);
		}
	}
	cout << flow.calc(numnodes - 2, numnodes - 1);

	return 0;
}
