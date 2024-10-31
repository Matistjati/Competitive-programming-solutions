#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
const int inf = int(1e9);

#include <bits/extc++.h>

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

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

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({ 0, s });

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				ll val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == q.end())
						its[e.to] = q.push({ -dist[e.to], e.to });
					else
						q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		repp(i, 0, N) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t) {
		ll totflow = 0, totcost = 0;
		int fc = -inf;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);

			int c = 0;
			for (edge* x = par[t]; x; x = par[x->from]) {
				c += fl * x->cost;
			}
			if (fc==-inf)
			{
				fc = c;
			}
			else
			{
				if (c!=fc)
				{
					break;
				}
			}
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

void dfs(int u, int t, vi& path, MCMF& flow)
{
	if (u == t) return;
	path.push_back(u);
	repe(e, flow.ed[u])
	{
		if (e.flow>0)
		{
			e.flow--;
			dfs(e.to, t, path, flow);
			return;
		}
	}
}

signed main()
{
	fast();

	int n;
	cin >> n;
	vector<ll> nums(n);
	rep(i, n) cin >> nums[i];

	int nodecnt = 2 * n + 2;
	MCMF flow(nodecnt);

	rep(i, n)
	{
		flow.addEdge(nodecnt - 2, i * 2, 1, 0);
		flow.addEdge(i*2+1, nodecnt-1, 1, 0);
		flow.addEdge(i*2, i*2+1, 1, -1);
		repp(j, i+1, n)
		{
			if (nums[i]%nums[j]==0||nums[j]%nums[i]==0)
			{
				flow.addEdge(i * 2 + 1, j * 2, 1, 0);
			}
		}
	}
	flow.setpi(nodecnt - 2);
	p2 ans = flow.maxflow(nodecnt - 2, nodecnt - 1);
	cout << -ans.second / ans.first << " " << ans.first << "\n";

	rep(i, ans.first)
	{
		vi path;
		dfs(nodecnt - 2, nodecnt - 1, path, flow);
		path.erase(path.begin());
		cout << path[0] / 2 + 1 << " ";
		repp(j, 2, sz(path))
		{
			if (path[j]/2 != path[j - 1]/2) cout << (path[j] / 2) + 1 << " ";
		}
		cout << "\n";
	}

	return 0;
}
