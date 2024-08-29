#include "simurgh.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll linf = ll(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct UF
{
	vi par;
	UF(int n) : par(n)
	{
		rep(i, n)par[i] = i;
	}
	int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		par[b] = a;
	}
};

vi spanning;
const int maxn = 500;
const int maxm = maxn * maxn;
int is_golden[maxm], vis[maxn], parnode[maxn], paredge[maxn];
int depth[maxn], visedge[maxm], maxup[maxn], known[maxm];

vector<p2> up_edges[maxn];
void dfs(int u, vector<vector<p2>>& edges)
{
	repe(e, edges[u])
	{
		if (vis[e.first]) // back edge
		{
			if (visedge[e.second]) continue;
			visedge[e.second] = 1;
			up_edges[u].push_back(e);
			maxup[u] = min(maxup[u], depth[e.first]);
		}
		else
		{
			depth[e.first] = depth[u] + 1;
			visedge[e.second] = 1;
			spanning.push_back(e.second);
			vis[e.first] = 1;
			parnode[e.first] = u;
			paredge[e.first] = e.second;
			dfs(e.first, edges);
			if (maxup[e.first]>=depth[e.first]) // bridge
			{
				is_golden[e.second] = 1;
				known[e.second] = 1;
			}
			maxup[u] = min(maxup[u], maxup[e.first]);
		}
	}
}

vi a, b;
int n;
int forest_query(vi edges)
{
	vi q;
	UF uf(n);
	repe(u, edges)
	{
		q.emplace_back(u);
		if (uf.find(a[u]) == uf.find(b[u])) assert(0);
		uf.merge(a[u], b[u]);
	}
	int num_good = 0;
	repe(s, spanning)
	{
		if (uf.find(a[s]) == uf.find(b[s])) continue;
		uf.merge(a[s], b[s]);
		num_good += is_golden[s];
		q.push_back(s);
	}
	assert(sz(q) < n);
	return count_common_roads(q) - num_good;
}

std::vector<int> find_roads(int N, std::vector<int> A, std::vector<int> B) {
	a = A;
	b = B;
	n = N;
	rep(i, maxn) maxup[i] = int(1e6);
	memset(is_golden, 0, sizeof(is_golden));
	memset(parnode, -1, sizeof(parnode));
	if (n==2)
	{
		return { 0 };
	}
	int m = sz(a);

	vector<vector<p2>> dedges(n);
	rep(i, m)
	{
		dedges[a[i]].emplace_back(b[i], i);
		dedges[b[i]].emplace_back(a[i], i);
	}
	vis[0] = 1;
	parnode[0] = 0;
	depth[0] = 0;
	dfs(0, dedges);
	parnode[0] = -1;
	repp(u, 1, n)
	{
		repe(e, up_edges[u])
		{
			vi cycle = { e.second };

			int num_unknown = 0;

			int v = u;
			while (v != 0 && v != e.first)
			{
				if (!known[paredge[v]]) num_unknown++;
				cycle.push_back(paredge[v]);
				v = parnode[v];
			}
			if (num_unknown == 0) continue;
			
			bool seen_known = 0;
			int mx = 0;
			vector<p2> res;
			rep(i, sz(cycle))
			{
				UF uf(n);
				vi q;
				rep(j, sz(cycle))
				{
					if (i == j) continue;
					q.push_back(cycle[j]);
					uf.merge(a[cycle[j]], b[cycle[j]]);
				}
				repe(u, spanning)
				{
					if (uf.find(a[u]) == uf.find(b[u])) continue;
					uf.merge(a[u], b[u]);
					q.push_back(u);
				}
				if (known[cycle[i]])
				{
					if (!seen_known)
					{
						seen_known = 1;
						int k = count_common_roads(q);
						if (!is_golden[cycle[i]])
						{
							mx = k;
						}
						else mx = k + 1;
					}
				}
				else
				{
					res.emplace_back(cycle[i], count_common_roads(q));
				}
				mx = max(mx, res.back().second);
			}
			
			repe(v, res)
			{
				if (v.second < mx)
				{
					is_golden[v.first] = 1;
				}
				known[v.first] = 1;
			}
		}
	}
	
	assert(sz(spanning) == n - 1);

	vector<set<int>> edges(n);
	rep(i, m)
	{
		edges[a[i]].insert(i);
		edges[b[i]].insert(i);
	}
	queue<int> leaf;
	vi deg(n);
	rep(i, n)
	{
		deg[i] = forest_query(vi(all(edges[i])));
		if (deg[i] == 1) leaf.push(i);
	}

	vi par(n, -1);
	while (sz(leaf))
	{
		int u = leaf.front();
		leaf.pop();

		if (deg[u] == 0) break;
		assert(deg[u] == 1);
		int lo = -1;
		int hi = sz(edges[u]);
		while (lo+1<hi)
		{
			int mid = (lo + hi) / 2;
			vi q;
			auto start = edges[u].begin();
			rep(i, mid + 1)
			{
				q.push_back(*start);
				start++;
			}
			if (forest_query(q))
			{
				hi = mid;
			}
			else lo = mid;
		}
		auto start = edges[u].begin();
		rep(i, hi) start = next(start);
		int e = *start;
		int v = a[e] == u ? b[e] : a[e];
		edges[v].erase(e);
		deg[v]--;
		if (deg[v]==1)
		{
			leaf.push(v);
		}
		par[u] = e;
	}

	vi r;
	rep(i, n) if (par[i] != -1)r.push_back(par[i]);
	int common = count_common_roads(r);
	assert(common == n - 1);
	return r;
}
