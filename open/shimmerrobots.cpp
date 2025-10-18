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

void dfs(int u, vi& vis, vi& order, vvi& adj)
{
	if (vis[u]==2) return;
	if (vis[u]==1)
	{
		cout << "-1\n";
		exit(0);
	}
	vis[u] = 1;

	repe(e, adj[u]) dfs(e, vis, order, adj);

	order.push_back(u);
	vis[u] = 2;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m, k;
	cin >> n >> m >> k;

	vvi adj(n + k);
	rep(i, m)
	{
		int a, b;
		char c;
		cin >> a >> b >> c;
		a--; b--;
		if (c=='A')
		{
			adj[a].push_back(n + b);
		}
		else
		{
			adj[b + n].push_back(a);
		}
	}

	vi vis(n + k);
	vi order;
	rep(i, n) dfs(i, vis, order, adj);

	reverse(all(order));
	repe(u, order) if (u<n) cout << u+1 << " ";
	cout << '\n';

	return 0;
}
