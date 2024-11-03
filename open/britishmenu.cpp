#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

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

void toposort(int u, vi& vis, vi& order, vvi& edges)
{
	if (vis[u]) return;
	vis[u] = 1;

	repe(e, edges[u]) toposort(e, vis, order, edges);
	order.push_back(u);
}

void dfs(int u, vi& vis, vi& comp, vvi& edges)
{
	if (vis[u]) return;
	vis[u] = 1;
	comp.push_back(u);
	repe(e, edges[u]) dfs(e, vis, comp, edges);
}

signed main()
{
	fast();

	int n, m;
	cin >> n >> m;
	vvi edges(n);
	vvi redges(n);
	rep(i, m)
	{
		int a, b;
		cin >> a >> b;
		a--; b--;

		edges[a].push_back(b);
		redges[b].push_back(a);
	}

	vi order;
	vi vis(n);
	rep(i, n) toposort(i, vis, order, edges);

	reverse(all(order));
	vis = vi(n);
	vi whichcomp(n, -1);
	int compind = 0;
	vvi comps;
	vector<map<p2, int>> scc_longest;
	repe(i, order)
	{
		if (vis[i]) continue;
		vi comp;
		dfs(i, vis, comp, redges);
		repe(u, comp) whichcomp[u] = compind;

		sort(all(comp));
		comps.push_back(comp);
		vector<p2> compedges;
		repe(u, comp)
		{
			repe(e, edges[u])
			{
				if (whichcomp[u] == whichcomp[e])
				{
					compedges.push_back(p2(u, e));
				}
			}
		}
		sort(all(compedges));

		map<p2, int> longest;
		do
		{
			repp(i, 1, sz(comp))
			{
				if (!binary_search(all(compedges), p2(comp[i - 1], comp[i]))) break;
				p2 p = p2(comp[0], comp[i]);
				longest[p] = max(longest[p], i);
			}
		} while (next_permutation(all(comp)));
		scc_longest.push_back(longest);
		compind++;
	}
	vvi cond_adj(compind);
	rep(i, n)
	{
		repe(e, edges[i])
		{
			int ic = whichcomp[i];
			int ec = whichcomp[e];
			if (ic != ec)
			{
				cond_adj[ic].push_back(ec);
			}
		}
	}

	order.resize(0);
	vis = vi(compind, 0);
	rep(i, compind) toposort(i, vis, order, cond_adj);
	reverse(all(order));

	vi dp(n, 1);
	repe(c, order)
	{
		map<int, int> newbest;
		repe(longest, scc_longest[c])
		{
			p2 p = longest.first;
			newbest[p.second] = max(newbest[p.second], dp[p.second]);
			newbest[p.second] = max(newbest[p.second], dp[p.first] + longest.second);
		}
		repe(w, newbest) dp[w.first] = max(dp[w.first], w.second);
		repe(u, comps[c])
		{
			repe(e, edges[u])
			{
				if (whichcomp[u] != whichcomp[e])
				{
					dp[e] = max(dp[e], dp[u] + 1);
				}
			}
		}
	}
	cout << *max_element(all(dp));

	return 0;
}
