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

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;

		vi points_in(n);
		vector<p2> matches;
		rep(i, n)
		{
			string row;
			cin >> row;
			repp(j, i + 1, n)
			{
				if (row[j] == '.') matches.emplace_back(i, j);
				if (row[j] == 'd') points_in[i]++, points_in[j]++;
				if (row[j] == '1') points_in[i] += 2;
				if (row[j] == '0') points_in[j] += 2;
			}
		}

		vi winners;
		rep(i, n)
		{
			vi points(points_in);
			repe(match, matches)
			{
				if (match.first == i || match.second == i) points[i] += 2;
			}
			int limit = points[i];
			int largest = 0;
			rep(j, n) if (i != j) largest = max(largest, points[j]);
			if (largest > limit) continue;
			// all are less than our best, can we assign all to be less than us?

			int nodecnt = n + sz(matches) + 2;
			PushRelabel flow(nodecnt);
			rep(j, n) if (i != j) flow.addEdge(sz(matches) + j, nodecnt - 1, limit - points[j]);
			int realmatches = 0;
			rep(j, sz(matches))
			{
				p2 match = matches[j];
				if (match.first == i || match.second == i) continue;
				realmatches++;
				flow.addEdge(j, match.first + sz(matches), 2);
				flow.addEdge(j, match.second + sz(matches), 2);
			}
			rep(j, sz(matches)) flow.addEdge(nodecnt - 2, j, 2);

			int f = flow.calc(nodecnt - 2, nodecnt - 1);
			if (f == realmatches * 2)
			{
				winners.push_back(i + 1);
			}
		}
		repe(w, winners) cout << w << " ";
		cout << "\n";
	}

	return 0;
}
