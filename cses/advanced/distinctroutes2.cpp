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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
	struct edge {
		int from, to, rev;
		ll cap, cost, flow;
	};
	int N;
	vector<vector<edge>> ed;
	vi seen;
	vector<ll> dist, pi;
	vector<edge*> par;

	MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		if (from == to) return;
		ed[from].push_back(edge{ from,to,sz(ed[to]),cap,cost,0 });
		ed[to].push_back(edge{ to,from,sz(ed[from]) - 1,0,-cost,0 });
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;

		priority_queue<pair<ll, int>> q;
		q.push({ 0, s });

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				ll val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					q.push({ -dist[e.to], e.to });
				}
			}
		}
		repp(i, 0, N) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t, int k) {
		ll totcost = 0;
		int its = 0;
		while ((path(s), seen[t]) && its < k) {
			its++;
			ll fl = 1;

			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
		}
		repp(i, 0, N) for (edge& e : ed[i]) totcost += e.cost * e.flow;
		return { its == k, totcost / 2 };
	}

	vi findpath(int s, int t)
	{
		rep(i, sz(par)) par[i] = nullptr;
		queue<int> q;
		q.push(s);
		par[t] = nullptr;

		while (q.size())
		{
			int u = q.front(); q.pop();
			if (u == t) break;

			repe(e, ed[u])
			{
				if (e.flow > 0 && par[e.to] == nullptr)
				{
					par[e.to] = &e;
					q.push(e.to);
				}
			}
		}
		if (par[t] == nullptr) return {};
		vi path;
		for (edge* x = par[t]; x; x = par[x->from]) {
			path.push_back(x->to);
			x->flow -= 1;
		}
		reverse(all(path));
		return path;
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(all(pi), INF); pi[s] = 0;
		int it = N, ch = 1; ll v;
		while (ch-- && it--)
			repp(i, 0, N) if (pi[i] != INF)
			for (edge& e : ed[i]) if (e.cap)
				if ((v = pi[i] + e.cost) < pi[e.to])
					pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};

signed main()
{
	fast();

	int n, m, k;
	cin >> n >> m >> k;
	MCMF flow(n);
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		flow.addEdge(a, b, 1, 1);
	}
	p2 res = flow.maxflow(0, n - 1, k);
	if (res.first)
	{
		cout << res.second << "\n";
		vi path;
		while (path = flow.findpath(0, n - 1), sz(path))
		{
			cout << sz(path) + 1 << "\n";
			cout << "1 ";
			repe(u, path) cout << u + 1 << " ";
			cout << "\n";
		}
	}
	else cout << "-1";

	return 0;
}
