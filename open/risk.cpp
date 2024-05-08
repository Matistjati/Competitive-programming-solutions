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


struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({ b, sz(adj[b]), c, c });
		adj[b].push_back({ a, sz(adj[a]) - 1, rcap, rcap });
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		int L = 30;
		do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
signed main()
{
	fast();

	int t;
	cin >> t;

	while (t--)
	{
		int n;
		cin >> n;
		vi numarmies(n);
		rep(i, n) cin >> numarmies[i];

		int numnodes = n * 2 + 2;
		Dinic flowsource(numnodes);

		vi adjenemy(n);
		rep(i, n)
		{
			string row;
			cin >> row;
			row[i] = 'Y';
			if (numarmies[i] == 0) continue;
			rep(j, n)
			{
				if (row[j] == 'N') continue;
				if (numarmies[j] == 0)
				{
					adjenemy[i] = 1;
					continue;
				}
				flowsource.addEdge(i, j + n, inf);
			}
		}
		rep(i, n)
		{
			flowsource.addEdge(numnodes - 2, i, numarmies[i]);
		}

		int lo = 0;
		int hi = int(1e5);
		while (lo + 1 < hi)
		{
			int mid = (hi + lo) / 2;
			Dinic flow(flowsource);
			int flowamount = 0;
			rep(i, n)
			{
				if (numarmies[i] == 0) continue;
				int c = adjenemy[i] ? mid : 1;
				flowamount += c;
				flow.addEdge(i + n, numnodes - 1, c);
			}

			if (flow.calc(numnodes - 2, numnodes - 1) == flowamount) lo = mid;
			else hi = mid;
		}
		cout << lo << "\n";
	}


	return 0;
}