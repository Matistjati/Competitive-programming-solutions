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

struct UF
{
	vi par;
	vi size;
	UF(int n) : par(n), size(n, 1)
	{
		rep(i, n) par[i] = i;
	}
	int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);
		par[b] = a;
		size[a] += size[b];
	}
};

const int maxn = 1e5 + 10;
int up[maxn], upw[maxn];
int tin[maxn], tout[maxn];

int timer = 0;
void dfs(int u, int p, int upweight, vector<vector<p2>>& adj)
{
	tin[u] = timer++;
	up[u] = p;
	upw[u] = upweight;
	repe(e, adj[u]) if (e.first != p) dfs(e.first, u, e.second, adj);
	tout[u] = timer++;
}

bool isancestor(int a, int b)
{
	return tin[a] <= tin[b] && tin[b] <= tout[a];
}


int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<tuple<int, int, int>> edges(m);
	rep(i, m)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		edges[i] = {c, a, b};
	}
	sort(all(edges));

	vi used(m);
	vector<vector<p2>> adj(n);
	UF uf(n);
	ll mst_weight = 0;
	int ind = 0;
	for (auto [w, a, b] : edges)
	{
		if (uf.find(a)!=uf.find(b))
		{
			used[ind]++;
			mst_weight += w;
			uf.merge(a, b);
			adj[a].emplace_back(b,w);
			adj[b].emplace_back(a,w);
		}
		ind++;
	}

	dfs(0, 0, 1e9, adj);

	ll ans = 0;

	vi deleted(n);
	vi ufpar(n);
	rep(i, n)ufpar[i] = i;
	auto find = [&](int x)
		{
			int u = x;
			while (deleted[u]) u = ufpar[u];
			int v = x;
			while (deleted[v])
			{
				int p = ufpar[v];
				ufpar[v] = u;
				v = p;
			}
			return u;
		};

	auto del = [&](int u)
		{
			deleted[u] = 1;
			ufpar[u] = up[u];
		};

	auto walk = [&](int a, int b, int w)
		{
			int u = find(a);
			while (!isancestor(u,b))
			{
				ans = max(ans, mst_weight + w - upw[u]);
				del(u);
				u = find(a);
			}
		};

	rep(i, m)
	{
		if (used[i]) continue;
		auto [w, a, b] = edges[i];
		walk(a, b, w);
		walk(b, a, w);
	}

	cout << ans << '\n';

	return 0;
}
