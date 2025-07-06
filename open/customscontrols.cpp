#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = 1e18;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

void toposort(int u, vi & vis, vi & order, vvi & adj)
{
	if (vis[u]) return;
	vis[u] = 1;
	repe(e, adj[u]) toposort(e, vis, order, adj);
	order.push_back(u);
}

signed main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m, k;
	cin >> n >> m >> k;
	vi w(n);
	rep(i, n) cin >> w[i];
	vvi adj(n);
	vector<p2> edges;
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
		edges.emplace_back(a, b);
	}

	if (find(all(edges),p2(0,n-1))!=end(edges)||find(all(edges),p2(n-1,0))!=end(edges))
	{
		if (n==2&&k==1)
		{
			cout << "impossible\n";
			return 0;
		}
		string ans(n, '$');
		if (k > 1)
		{
			ans[0] = 'N';
			ans.back() = 'N';
			k -= 2;
		}
		else
		{
			ans[0] = 'S';
			ans.back() = 'S';
		}
		rep(i, n)
		{
			if (ans[i] == '$')
			{
				if (k) ans[i] = 'N',k--;
				else ans[i] = 'S';
			}
		}
		cout << ans << "\n";
		return 0;
	}

	priority_queue<p2> pq;
	pq.emplace(0, 0);
	vi dist(n,inf);
	dist[0] = 0;
	while (sz(pq))
	{
		auto [d, u] = pq.top();
		pq.pop();
		d = -d;
		if (d > dist[u]) continue;
		
		repe(e, adj[u])
		{
			if (d+w[e]<dist[e])
			{
				dist[e] = d + w[e];
				pq.emplace(-d - w[e], e);
			}
		}
	}

	vvi dagadj(n);
	for (auto [u, v] : edges)
	{
		if (dist[u]+w[v]==dist[v])
		{
			//cout << u << " " << v << "\n";
			dagadj[u].push_back(v);
		}
		if (dist[v] + w[u] == dist[u])
		{
			//cout << v << " " << u << "\n";
			dagadj[v].push_back(u);
		}
	}

	vi vis(n);
	vi order;
	rep(i, n) toposort(i, vis, order, dagadj);
	reverse(all(order));

	string ans(n,'$');
	rep(i, k)
	{
		ans[order[i]] = 'N';
	}
	repp(i, k, n)
	{
		ans[order[i]] = 'S';
	}
	cout << ans << "\n";

	return 0;
}
