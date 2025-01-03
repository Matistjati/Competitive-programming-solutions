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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

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

	int n;
	cin >> n;
	const int r = 12;
	int arr[r][r][r];
	memset(arr, 0, sizeof(arr));
	int numnodes = r * r * r + 2;
	PushRelabel flow(numnodes);

	rep(i, n)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a++; b++; c++;
		arr[a][b][c] = 1;
	}

	auto hashp = [&](int i, int j, int k)
		{
			return i + j * r + k * r * r;
		};

	vector<tuple<int, int, int>> dirs = {
		{0,0,1},
		{0,0,-1},
		{0,1,0},
		{0,-1,0},
		{1,0,0},
		{-1,0,0},
	};
	rep(i, r) rep(j, r) rep(k, r)
	{
		if (arr[i][j][k]) flow.addEdge(numnodes - 2, hashp(i, j, k), 6);
		else if (i==0||j==0||k==0||i==r-1||j==r-1||k==r-1)
		{
			flow.addEdge(hashp(i, j, k), numnodes - 1, inf);
		}

		repe(dir, dirs)
		{
			int a = i + get<0>(dir);
			int b = j + get<1>(dir);
			int c = k + get<2>(dir);
			if (a < 0 || b < 0 || c < 0 || a >= r || b >= r || c >= r) continue;
			flow.addEdge(hashp(i, j, k), hashp(a, b, c), 1);
		}
	}
	cout << flow.calc(numnodes - 2, numnodes - 1);
	

    return 0;
}
