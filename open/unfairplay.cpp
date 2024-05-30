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

	int n, m;
	while (cin >> n >> m && n != -1)
	{
		vi points(n);
		rep(i, n) cin >> points[i];
		vi pc(points);

		vector<p2> matches;
		int ourpoints = points.back();
		int forcedwin = 0;
		rep(i, m)
		{
			int a, b;
			cin >> a >> b;
			a--; b--;
			matches.emplace_back(a, b);
			if (a == n - 1) points[a] += 2, forcedwin++;
			if (b == n - 1) points[b] += 2, forcedwin++;
		}

		int nodecnt = n + m + 2;
		PushRelabel flow(nodecnt);
		int limit = points.back() - 1;
		rep(i, n - 1)
		{
			flow.addEdge(i + m, nodecnt - 1, limit - points[i]);
		}
		rep(i, m)
		{
			if (matches[i].first == n - 1 || matches[i].second == n - 1) continue;
			flow.addEdge(nodecnt - 2, i, 2);
			flow.addEdge(i, matches[i].first + m, 2);
			flow.addEdge(i, matches[i].second + m, 2);
		}

		int largest = 0;
		rep(i, n - 1) largest = max(largest, points[i]);

		if (largest < points.back() && flow.calc(nodecnt - 2, nodecnt - 1) == 2 * (m - forcedwin))
		{

			rep(i, m)
			{
				if (matches[i].first == n - 1 || matches[i].second == n - 1)
				{
					if (matches[i].first == n - 1) cout << "0 ", pc.back() += 2;
					else cout << "2 ", pc.back() += 2;
				}
				else
				{
					int v = -1;
					repe(e, flow.g[i])
					{
						if (e.dest == matches[i].first + m) v = e.f;
					}
					assert(v >= 0);
					if (v == 1) cout << "1 ", pc[matches[i].first]++, pc[matches[i].second]++;
					else if (v == 2) cout << "0 ", pc[matches[i].first] += 2;
					else cout << "2 ", pc[matches[i].second] += 2;
				}
			}

			rep(i, n - 1) assert(pc[i] < pc.back());
		}
		else cout << "NO\n";
	}

	return 0;
}
