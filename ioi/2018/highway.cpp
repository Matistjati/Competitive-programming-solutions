#include "highway.h"

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

typedef long long ll;

void find_pair(int n, std::vector<int> U, std::vector<int> V, int A, int B)
{
	int m = sz(U);

	ll baseline = ask(vi(m, 0));

	int lo = -1;
	int hi = m;
	while (lo+1<hi)
	{
		int mid = (lo + hi) / 2;
		vi w(m);
		rep(i, mid + 1) w[i] = 1;
		if (ask(w) > baseline)
		{
			hi = mid;
		}
		else lo = mid;
	}

	int u = U[hi];
	int v = V[hi];
	vector<vector<p2>> edges(n);
	rep(i, m)
	{
		int a = U[i];
		int b = V[i];
		edges[a].emplace_back(b, i);
		edges[b].emplace_back(a, i);
	}
	
	vi ans;

	rep(_, 2)
	{
		vi istree(m);
		vi edgedist(m);
		vi nodedist(n);
		priority_queue<tuple<int,int,int>> q;
		vi vis(n);

		q.emplace(-1, -1, u);
		while (sz(q))
		{
			int d, s, a;
			tie(d, s, a) = q.top();
			q.pop();

			nodedist[a] = -d*s;
			repe(e, edges[a])
			{
				if (vis[e.first])
				{
					if (edgedist[e.second]==0)
					{
						edgedist[e.second] = -int(1e7);
					}
				}
				else
				{
					vis[e.first] = 1;
					istree[e.second] = 1;
					edgedist[e.second] = -d * s * (e.first == v ? -1 : 1);
					q.emplace(d - 1, s * (e.first == v ? -1 : 1), e.first);
				}
			}
		}
		nodedist[u] = -int(1e6);

		vector<p2> edge_order;
		rep(i, m) edge_order.emplace_back(edgedist[i], i);
		sort(edge_order.rbegin(), edge_order.rend());

		lo = -1;
		hi = n;
		for (int i = m-1; i >= 0; i--) if (edge_order[i].first < 0) hi = i;
		while (lo+1<hi)
		{
			int mid = (lo + hi) / 2;
			vi w(m);
			rep(i, m)
			{
				if (!istree[i]) w[i] = 1;
			}
			rep(i, mid + 1) w[edge_order[i].second] = 1;
			if (ask(w) > baseline)
			{
				hi = mid;
			}
			else lo = mid;
		}
		int e = edge_order[hi].second;
		ans.push_back(nodedist[U[e]]>nodedist[V[e]]?U[e]:V[e]);
		swap(u, v);
	}
	

	answer(ans[0], ans[1]);
}
