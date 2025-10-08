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
#define sz(x) ((int)(x).size())


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


int main()
{
	int N, Q, S;
	cin >> N >> Q >> S;

	vi sensor_to_queue(S);
	repe(s, sensor_to_queue) cin >> s, s--;
    
	vi queue_size_limit(Q);
	repe(l, queue_size_limit) cin >> l;

	vi transfer_limit(N);
	vvi downlink_data_amount(N, vi(Q));
	rep(n, N)
	{
		cin >> transfer_limit[n];
		rep(s, S)
		{
			int data_amount;
			cin >> data_amount;
			downlink_data_amount[n][sensor_to_queue[s]] += data_amount;
		}
	}

	int nodes_per_layer = (Q * 2 + 1);
	int num_nodes = nodes_per_layer * N+2;
	int source = num_nodes - 1;
	int sink = num_nodes - 2;

	auto get_input_hatch = [&](int layer, int queue_ind)
	{
		return nodes_per_layer * layer + queue_ind;
	};
	auto get_queue_limiter = [&](int layer, int queue_ind)
	{
		return nodes_per_layer * layer + Q + queue_ind;
	};
	auto get_downlink_limiter = [&](int layer)
	{
		return nodes_per_layer * layer + 2*Q;
	};

	PushRelabel flow(num_nodes);

	rep(layer, N)
	{
		flow.addEdge(get_downlink_limiter(layer), sink, transfer_limit[layer]);
		rep(q, Q)
		{
			flow.addEdge(source, get_input_hatch(layer, q), downlink_data_amount[layer][q]);
			flow.addEdge(get_input_hatch(layer, q), get_queue_limiter(layer, q), queue_size_limit[q]);
			flow.addEdge(get_queue_limiter(layer, q), get_downlink_limiter(layer), inf);
			if (layer<N-1)
			{
				flow.addEdge(get_queue_limiter(layer, q), get_input_hatch(layer + 1, q), inf);
			}
		}
	}

	ll total_data = 0;
	rep(n, N) total_data += accumulate(all(downlink_data_amount[n]), 0LL);
	cout << (flow.calc(source, sink)== total_data ? "possible" : "impossible") << '\n';

    return 0;
}
