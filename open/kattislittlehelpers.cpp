#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
//const int inf = int(1e18);
const int inf = int(1e9);

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
#define __builtin_popcount popcount
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

	pair<ll, ll> maxflow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);
			ll c = 0;
			for (edge* x = par[t]; x; x = par[x->from])
				c += x->cost;

			if (c > 0) break;

			totflow += fl;
			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
		}
		repp(i, 0, N) for (edge& e : ed[i]) totcost += e.cost * e.flow;
		return { totflow, totcost / 2 };
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

	int r, c, b, t;
	cin >> c >> r >> b >> t;
	vector<vvi> whomst(r, vvi(c));

	vector<string> grid(r);
	rep(i, r) cin >> grid[i];
	p2 goal;
	rep(i, r) rep(j, c) if (grid[i][j] == 'K') goal = p2(i, j);
	vector<p2> targets;
	rep(i, t)
	{
		int a, b;
		cin >> b >> a;
		a--; b--;
		targets.emplace_back(a, b);
	}
	t++;
	targets.push_back(goal);
	rep(i, t)
	{
		whomst[targets[i].first][targets[i].second].push_back(i);
	}

	typedef tuple<int, int, int> p3;
	vvi dist(t, vi(t, inf));
	vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
	rep(i, t)
	{
		queue<p3> q;
		q.emplace(0, targets[i].first, targets[i].second);
		vvi vis(r, vi(c));
		while (q.size())
		{
			int d, a, b;
			tie(d, a, b) = q.front();
			q.pop();
			if (vis[a][b]) continue;
			vis[a][b] = 1;
			repe(w, whomst[a][b]) dist[i][w] = d;

			repe(dir, dirs)
			{
				p2 np = p2(a + dir.first, b + dir.second);
				if (np.first < 0 || np.second < 0 || np.first >= r || np.second >= c) continue;
				if (grid[np.first][np.second] == '#') continue;
				q.emplace(d + 1, np.first, np.second);
			}
		}
	}
	rep(i, t)
	{
		if (dist[i][t - 1] == inf)
		{
			cout << "impossible";
			return 0;
		}
	}
	int nodecnt = (t - 1) * 2 + 3;
	MCMF flow(nodecnt);

	flow.addEdge(nodecnt - 2, nodecnt - 3, b, 0);
	rep(i, t - 1)
	{
		flow.addEdge(nodecnt - 3, i * 2, inf, dist[t - 1][i]);
	}
	rep(i, t - 1)
	{
		flow.addEdge(i * 2, i * 2 + 1, 1, -inf);
	}
	rep(i, t - 1)
	{
		flow.addEdge(i * 2 + 1, nodecnt - 1, inf, dist[i][t - 1]);
	}
	rep(i, t - 1)
	{
		repp(j, i + 1, t - 1)
		{
			flow.addEdge(i * 2 + 1, j * 2, inf, dist[i][j]);
		}
	}
	flow.setpi(nodecnt - 2);
	p2 f = flow.maxflow(nodecnt - 2, nodecnt - 1);
	cout << f.second + (t - 1) * inf;

	return 0;
}
