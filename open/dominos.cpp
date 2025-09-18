#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

void toposort(int u, vi& vis, vi& order, vvi& adj)
{
	if (vis[u]) return;
	vis[u] = 1;
	repe(e, adj[u]) toposort(e, vis, order, adj);
	order.push_back(u);
}

void dfs2(int u, int c, vi& whichcomp, vvi& adj)
{
	if (whichcomp[u] != -1) return;
	whichcomp[u] = c;
	repe(e, adj[u]) dfs2(e, c, whichcomp, adj);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--)
	{
		int n, m;
		cin >> n >> m;

		vector<p2> edges;
		vvi adj(n);
		vvi radj(n);
		rep(i, m)
		{
			int a, b;
			cin >> a >> b;
			a--; b--;
			adj[a].push_back(b);
			radj[b].push_back(a);
			edges.emplace_back(a, b);
		}
		vi vis(n);
		vi order;
		rep(i, n) toposort(i, vis, order, adj);
		reverse(all(order));

		vi whichcomp(n,-1);
		int cc = 0;
		repe(u, order)
		{
			if (whichcomp[u] != -1) continue;
			dfs2(u, cc++, whichcomp, radj);
		}
		vi indeg(cc);
		for (auto [a, b] : edges)
		{
			a = whichcomp[a];
			b = whichcomp[b];
			if (a != b) indeg[b]++;
		}
		int ans = 0;
		rep(i, cc) ans += indeg[i] == 0;
		cout << ans << '\n';
	}

	return 0;
}
