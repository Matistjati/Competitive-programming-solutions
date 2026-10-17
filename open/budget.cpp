#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())


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
		g[s].push_back({ t, (int)sz(g[t]), 0, cap });
		g[t].push_back({ s, (int)sz(g[s]) - 1, 0, rcap });
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
flowAlgorithm* lowerbound_flow(vector<edge>& edges, int n, int source, int sink, int capacity=1e9)
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
		flow->addEdge(i, n+1, outflow[i]);
	}
	flow->addEdge(sink, source, capacity);

	return flow->calc(n,n+1)==accumulate(all(outflow),0)?flow:nullptr;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
	while (t--) {
        int n,m;
        cin >> n >> m;
		vi rowsums(n);
		vi colsums(m);
        rep(i,n) cin >> rowsums[i];
        rep(i,m) cin >> colsums[i];

        int k;
        cin >> k;
		vector<edge> edges;
		vvi low(n,vi(m,0));
		vvi hi(n, vi(m,1e9));
		rep(i, k) {
            int a,b,v;
            char c;
            cin >> a >> b >> c >> v;
			a--; b--;
			p2 upd = { -1e9,1e9 };
			if (c == '>') upd.first = v+1;
			if (c == '<') upd.second = v-1;
			if (c == '=') upd = p2(v,v);

			if (a==-1&&b==-1)
			{
				rep(i, n)rep(j, m) low[i][j] = max(low[i][j], upd.first);
				rep(i, n)rep(j, m) hi[i][j] = min(hi[i][j], upd.second);
			}
			else if (a==-1)
			{
				rep(i, n) low[i][b] = max(low[i][b], upd.first);
				rep(i, n) hi[i][b] = min(hi[i][b], upd.second);
			}
			else if (b==-1)
			{
				rep(j, m) low[a][j] = max(low[a][j], upd.first);
				rep(j, m) hi[a][j] = min(hi[a][j], upd.second);
			}
			else
			{
				low[a][b] = max(low[a][b], upd.first);
				hi[a][b] = min(hi[a][b], upd.second);
			}
		}
		
		rep(i, n)
		{
			edges.emplace_back(edge{ n + m,i,rowsums[i],rowsums[i] });
		}
		rep(i, m)
		{
			edges.emplace_back(edge{ n+i,n+m+1, colsums[i],colsums[i] });
		}
		int lowsum = accumulate(all(rowsums), 0) + accumulate(all(colsums), 0);
		rep(i, n)
		{
			rep(j, m)
			{
				edges.emplace_back(edge{ i,n + j, low[i][j],hi[i][j] });
				lowsum += low[i][j];
			}
		}


		PushRelabel* flowptr = lowerbound_flow(edges, n + m + 2, n + m, n + m + 1);

		if (flowptr !=nullptr)
		{
			PushRelabel flow = *flowptr;
			vvi ans(n, vi(m));
			rep(i, flow.g.size())
			{
				repe(e, flow.g[i])
				{
					if (i<n&&(e.dest>=n&&e.dest<n+m))
					{
						ans[i][e.dest - n] += e.f;
					}
				}
			}
			rep(i, n)
			{
				rep(j, m)
				{
					cout << (low[i][j] + ans[i][j]) << " ";
				}
				cout << "\n";
			}
		}
		else
		{
			cout << "IMPOSSIBLE";
			cout << "\n";
		}
	}

    return 0;
}
